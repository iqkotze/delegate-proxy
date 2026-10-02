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
CMP = r'(?:streq|strcaseeq|strcmp|strcasecmp|strneq|strncmp|strncasecmp|strncaseeq|isinList|isinListX|parameq)'
SYM = re.compile(r'const\s+char\s*\*?\s*(\w+)\s*(?:\[\])?\s*=\s*"([^"]+)"\s*;')
# Parameter to option parser: functions (file, name), option variables, aliases, mode
SUBS = {
    'MAXIMA': dict(funcs=[('delegate/src/env.cpp', 'maxima1')], vars='name'),
    'TIMEOUT': dict(funcs=[('delegate/src/env.cpp', 'timeout1')], vars='name'),
    'TLSCONF': dict(funcs=[('delegate/filters/sslway.cpp', 'scan_TLSCONF1')], vars='what'),
    'HTTPCONF': dict(funcs=[('delegate/src/httpd.cpp', 'scan_HTTPCONF'), ('delegate/src/httpd.cpp', 'settout'),
                            ('delegate/src/httpd.cpp', 'setmax')], vars='what'),
    'FTPCONF': dict(funcs=[('delegate/src/ftp.cpp', 'conf1')], vars='what'),
    'SMTPCONF': dict(funcs=[('delegate/src/smtp.cpp', 'scan1')], vars='nam'),
    'NNTPCONF': dict(funcs=[('delegate/src/nntp.cpp', 'scan1')], vars='what'),
    'POPCONF': dict(funcs=[('delegate/src/pop.cpp', 'scan1')], vars='nam'),
    'DNSCONF': dict(funcs=[('delegate/src/domain.cpp', 'scanconf1')], vars='name'),
    'ICPCONF': dict(funcs=[('delegate/src/icp.cpp', 'scan_ICPCONF')], vars='name'),
    'TELNETCONF': dict(funcs=[('delegate/src/telnet.cpp', 'scan_TELNETCONF')], vars='what'),
    'SOXCONF': dict(funcs=[('delegate/src/sox.cpp', 'scan_SOXCONF')], vars='what'),
    'YYCONF': dict(funcs=[('delegate/src/X.cpp', 'scan_YYCONF')], vars='nam', fold=False),
    'ARPCONF': dict(funcs=[('delegate/src/inets.cpp', 'scan_ARPCONF')], vars='nam'),
    'PAMCONF': dict(funcs=[('delegate/src/access.cpp', 'scan_PAMCONF')], vars='name'),
    'MHGWCONF': dict(funcs=[('delegate/src/nntpgw.cpp', 'scan_MHGWCONF')], vars='what'),
    'DELAY': dict(funcs=[('delegate/src/env.cpp', 'delay1')], vars='what'),
    'SOCKOPT': dict(funcs=[('delegate/src/inets.cpp', 'conf1'), ('delegate/src/service.cpp', 'CTX_defSockOpts')],
                    vars='name'),
    'IPV6': dict(funcs=[('delegate/src/inets.cpp', 'ipconf1')], vars='nameb'),
    'HTMLCONV': dict(funcs=[('delegate/rary/html.cpp', 'hconv1')], vars='conv'),
    'MIMECONV': dict(funcs=[('delegate/mimekit/mime.cpp', 'conv1'), ('delegate/mimekit/mime.cpp', 'scan_MIMECONV')],
                     vars='spec|convspec'),
    'COUNTER': dict(funcs=[('delegate/src/bcounter.cpp', 'scan_COUNTER1')], vars='sp1'),
    'CACHE': dict(funcs=[('delegate/src/conf.cpp', 'scan_CACHE1'), ('delegate/src/conf.cpp', 'set_CACHE')],
                  vars='spec|cache'),
    'SYSLOG': dict(funcs=[('delegate/src/syslog.cpp', 'scan_SYSLOG')], mode='syslog', fold=False),
    'DGDEF': dict(funcs=[('delegate/src/env.cpp', 'scan_DGDEF')], vars='flags'),
    'STLS': dict(funcs=[('delegate/src/stls.cpp', 'scan_STLS')], vars='opt1|op',
                 alias={'sv': 'fsv', 'cl': 'fcl', 'mim': 'mitm', '-im': 'im'}),
    'RELAY': dict(funcs=[('delegate/src/access.cpp', 'scan_relay1')], vars='r1'),
    'CONNECT': dict(funcs=[('delegate/src/master.cpp', 'connect1')], mode='char', fold=False),
    'DYCONF': dict(funcs=[('delegate/src/env.cpp', 'scanOpt1')], vars='name'),
    'MOUNT': dict(funcs=[], mode='mount'),
}
# MountOptions outside the table: option -> (file, text that must occur there)
MOUNT_EXTRA = {
    'charset': ('delegate/src/ddi.cpp', 'P_CHARSET'), 'ffromsv': ('delegate/src/ddi.cpp', 'FFROMSV='),
    'fsv': ('delegate/src/ddi.cpp', 'FSV='), 'stls': ('delegate/src/ddi.cpp', 'STLS='),
    'public': ('delegate/src/ddi.cpp', '"public"'), 'rident': ('delegate/src/ddi.cpp', '"rident"'), 'maxima': ('delegate/src/ddi.cpp', 'MAXIMA=bps:'),
    'counter': ('delegate/src/ddi.cpp', 'COUNTER='), 'baseurl': ('delegate/src/ddi.cpp', 'BASEURL='),
    'httpconf': ('delegate/src/ddi.cpp', 'HTTPCONF='), 'ftpconf': ('delegate/src/ddi.cpp', 'FTPCONF='),
    'pathext': ('delegate/src/ddi.cpp', 'pathext='), 'asis': ('delegate/src/ddi.cpp', '"asis"'),
    'servon': ('delegate/src/ftp.cpp', '"servon"'), 'timeout': ('delegate/src/ftp.cpp', '"timeout"'),
    'rewaddr': ('delegate/src/nntpgw.cpp', '"rewaddr"'), 'realm': ('delegate/src/httpd.cpp', '"realm="'),
    'search': ('delegate/src/httpd.cpp', '"search:"'), 'noanon': ('delegate/src/ftp.cpp', '"noanon"'),
    'logindir': ('delegate/src/ftp.cpp', '"logindir"'), 'ftpxhttp': ('delegate/src/ftp.cpp', '"ftpxhttp"'),
    'noseek': ('delegate/src/ftpgw.cpp', '"noseek"'), 'px-thruresp': ('delegate/src/http.cpp', '"px-thruresp"'),
    'recursive': ('delegate/src/httphead.cpp', '"recursive"'),
}


def load_generator():
    spec = importlib.util.spec_from_file_location('gen_params', os.path.join(HERE, 'gen-params.py'))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def read(path):
    with open(path, 'rb') as f:
        return f.read().decode('utf-8', 'replace')


def strip_comments(text):
    out = []
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        if c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            out.append(text[i:j + 1])
            i = j + 1
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            i = n if j < 0 else j + 2
        elif text.startswith('//', i):
            j = text.find('\n', i)
            i = n if j < 0 else j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


def function_body(text, name):
    m = re.search(r'^(?:static\s+)?[\w\s\*]*?\b%s\s*\([^;{]*?\)\s*\{' % re.escape(name), text, re.M | re.S)
    if not m:
        return ''
    end = re.search(r'^}', text[m.end():], re.M)
    return strip_comments(text[m.end():m.end() + end.start()] if end else text[m.end():])


def option_names(body, var, symbols):
    """Names compared with the option variable: exact names, prefix families (var+N) and symbols."""
    names = set()
    lit = r'\(\s*(?:%s)\s*,\s*"([^"]+)"' % var
    for m in re.finditer(CMP + lit, body):
        names.add(m.group(1))
    for m in re.finditer(r'\bstreq\(\s*(?:%s)\s*,\s*(\w+)\s*\)' % var, body):
        if m.group(1) in symbols:
            names.add(symbols[m.group(1)])
    for m in re.finditer(r'\b(?:streq|strcaseeq)\(\s*(?:%s)\s*\+\s*(\d+)\s*,\s*"([^"]+)"' % var, body):
        pre = [p for p in re.finditer(r'\b(?:strncmp|strncasecmp|strneq|strncaseeq)\(\s*(?:%s)\s*,\s*"([^"]+)"\s*,\s*%s\s*\)'
                                       % (var, m.group(1)), body[:m.start()])]
        if pre:
            names.add(pre[-1].group(1) + m.group(2))
    return names


def normalize(name):
    name = re.split(r'[:=/]', name)[0] if not name.startswith('-') else name
    return name


def opt_char(rec):
    m = re.search(r'\((.)\)', rec['syntax'])
    return m.group(1) if m else rec['name'][:1]


def char_names(body):
    return {'case:' + c for c in re.findall(r"case\s+'(.)'\s*:", body)}


def syslog_names(body):
    names = set()
    sw = re.search(r"case\s+'v'\s*:\s*switch\s*\(\s*cp\[2\]\s*\)\s*\{(.*?)\n\t\t    \}", body, re.S)
    for c in re.findall(r"case\s+'(.)'\s*:", sw.group(1) if sw else ''):
        names.add('-v' + c)
    if re.search(r"case\s+'s'\s*:", body):
        names.add('-sname')
    if re.search(r"case\s+'f'\s*:", body):
        names.add('-fname')
    return names


def mount_names(root):
    text = strip_comments(read(os.path.join(root, 'delegate/src/mount.cpp')))
    symbols = {m.group(1): m.group(2) for m in SYM.finditer(text)}
    m = re.search(r'mount_opts\[\]\s*=\s*\{(.*?)\n\};', text, re.S)
    names = set()
    for e in re.finditer(r'^\s*\{\s*\w+\s*,\s*(?:"([^"]+)"|(\w+))', m.group(1) if m else '', re.M):
        names.add(e.group(1) or symbols.get(e.group(2), e.group(2)))
    return names


def used_sub_options(root, problems):
    subs = {}
    for parent, spec in SUBS.items():
        fold = spec.get('fold', True)
        alias = spec.get('alias', {})
        mode = spec.get('mode', 'literal')
        found = {}
        for path, func in spec['funcs']:
            text = read(os.path.join(root, path))
            symbols = {m.group(1): m.group(2) for m in SYM.finditer(text)}
            body = function_body(text, func)
            if not body:
                problems.append('%s: function %s of %s not found' % (path, func, parent))
                continue
            if mode == 'syslog':
                names = syslog_names(body)
            elif mode == 'char':
                names = char_names(body)
            else:
                names = {normalize(n) for n in option_names(body, spec['vars'], symbols)}
            for n in names:
                found[n] = path
        if mode == 'mount':
            for n in mount_names(root):
                found[n] = 'delegate/src/mount.cpp'
            for n, (path, needle) in MOUNT_EXTRA.items():
                if needle.lower() in read(os.path.join(root, path)).lower():
                    found[n] = path
                else:
                    problems.append('%s: MOUNT option %s: %s not found' % (path, n, needle))
        for n, path in found.items():
            if n.endswith('-'):
                continue
            n = alias.get(n.lower() if fold else n, n)
            if n is None:
                continue
            subs[(parent, n.lower() if fold else n)] = path
    return subs


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
    used_subs = used_sub_options(root, problems)
    declared = {}
    for key, rec in reg.subs.items():
        fold = SUBS.get(key[0], {}).get('fold', True)
        declared[(key[0], key[1].lower() if fold else key[1])] = rec
    char_parents = {p for p, spec in SUBS.items() if spec.get('mode') == 'char'}
    for key in sorted(set(used_subs) - set(declared)):
        if key[0] in char_parents:
            if key[1][5:] in {opt_char(r) for k, r in declared.items() if k[0] == key[0]}:
                continue
            problems.append('%s: %s option %s has no DG_PARAM_SUB' % (used_subs[key], key[0], key[1][5:]))
        else:
            problems.append('%s: %s option %s has no DG_PARAM_SUB' % (used_subs[key], key[0], key[1]))
    for key in sorted(set(declared) - set(used_subs)):
        rec = declared[key]
        if key[0] in char_parents and 'case:' + opt_char(rec) in {k[1] for k in used_subs if k[0] == key[0]}:
            continue
        problems.append('%s:%d: DG_PARAM_SUB %s/%s, but the code does not read it' % (rec['file'], rec['line'], key[0], key[1]))
    for p in problems:
        print(p, file=sys.stderr)
    print('parameters: %d public, %d internal, %d sub-options, %d problems' % (
        len(reg.params), len(reg.internal), len(reg.subs), len(problems)))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
