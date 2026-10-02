#!/usr/bin/env python3
"""Reports parameters read by the code without a DG_PARAM declaration and declarations without use.

Usage: tools/check-params.py [--root DIR]
Exit code 1 on gaps or invalid declarations.
"""
import argparse
import importlib.util
import os
import re
import sys

sys.dont_write_bytecode = True
HERE = os.path.dirname(os.path.abspath(__file__))
PARAM_DEF = re.compile(r'^char\s+P_\w+\[\]\s*=\s*"([^"]*)"\s*;', re.M)
LITERAL = re.compile(r'\b\w*getEnv\w*\s*\(\s*"([A-Z][A-Z0-9_]*)"')
SUB_NAME = re.compile(r'streq\(\s*name\s*,\s*"([^"]+)"\s*\)')
TLS_SUB_NAME = re.compile(r'strcaseeq\(\s*what\s*,\s*"([^"]+)"\s*\)')
# parameter: (source file, function evaluating the options, pattern of the option names)
SUB_FUNCS = {
    'MAXIMA': ('delegate/src/env.cpp', 'maxima1', SUB_NAME),
    'TIMEOUT': ('delegate/src/env.cpp', 'timeout1', SUB_NAME),
    'TLSCONF': ('delegate/filters/sslway.cpp', 'scan_TLSCONF1', TLS_SUB_NAME),
}


def load_generator():
    spec = importlib.util.spec_from_file_location('gen_params', os.path.join(HERE, 'gen-params.py'))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def read(path):
    with open(path, 'rb') as f:
        return f.read().decode('utf-8', 'replace')


def function_body(text, name):
    m = re.search(r'^static\s+\w+\s+%s\s*\(' % re.escape(name), text, re.M)
    if not m:
        return ''
    end = re.search(r'^}', text[m.end():], re.M)
    return text[m.end():m.end() + end.start()] if end else text[m.end():]


def used_parameters(gen, root):
    names = {}
    param_cpp = os.path.join(root, 'delegate', 'src', 'param.cpp')
    for n in PARAM_DEF.findall(read(param_cpp)):
        if not n.startswith('_'):
            names.setdefault(n, 'delegate/src/param.cpp')
    for path in gen.source_files(root):
        rel = os.path.relpath(path, root)
        for n in LITERAL.findall(read(path)):
            names.setdefault(n, rel)
    return names


def used_sub_options(root):
    subs = {}
    for parent, (path, func, pattern) in SUB_FUNCS.items():
        text = read(os.path.join(root, path))
        for n in pattern.findall(function_body(text, func)):
            subs[(parent, n)] = path
    return subs


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--root', default=os.path.join(HERE, '..'))
    args = ap.parse_args()
    root = os.path.abspath(args.root)
    gen = load_generator()
    reg = gen.load(root)
    problems = list(reg.errors)
    declared = set(reg.params) | set(reg.internal)
    used = used_parameters(gen, root)
    for n in sorted(set(used) - declared):
        problems.append('%s: parameter %s has no DG_PARAM' % (used[n], n))
    for n in sorted(declared - set(used)):
        where = reg.params[n]['file'] if n in reg.params else reg.internal[n]
        problems.append('%s: DG_PARAM for %s, but the code does not read it' % (where, n))
    used_subs = used_sub_options(root)
    for key in sorted(set(used_subs) - set(reg.subs)):
        problems.append('%s: %s option %s has no DG_PARAM_SUB' % (used_subs[key], key[0], key[1]))
    for key in sorted(set(reg.subs) - set(used_subs)):
        rec = reg.subs[key]
        problems.append('%s:%d: DG_PARAM_SUB %s/%s, but the code does not read it' % (rec['file'], rec['line'], key[0], key[1]))
    for p in problems:
        print(p, file=sys.stderr)
    print('parameters: %d public, %d internal, %d sub-options, %d problems' % (
        len(reg.params), len(reg.internal), len(reg.subs), len(problems)))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
