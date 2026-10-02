#!/usr/bin/env python3
"""Reads DG_PARAM, DG_PARAM_SUB and DG_PARAM_INTERNAL from delegate/**/*.cpp,
validates them and writes the C++ parameter table and the Markdown reference.

Usage: tools/gen-params.py [--root DIR] [--table FILE] [--md FILE]
Without --table and --md the declarations are only validated.
"""
import argparse
import os
import re
import sys

MACRO = re.compile(r'^\s*(DG_PARAM_SUB|DG_PARAM_INTERNAL|DG_PARAM)\s*\((.*)\)\s*(?://.*)?$')
IDENT = re.compile(r'\s*([A-Za-z_]\w*)\s*')
STRING = re.compile(r',\s*"((?:[^"\\]|\\.)*)"\s*')
NAME_OK = re.compile(r'^[A-Z][A-Z0-9_]*$')
ESCAPES = {'n': '\n', 't': '\t'}
MAX_DESC = 100
NSTR = {'DG_PARAM': 4, 'DG_PARAM_SUB': 5, 'DG_PARAM_INTERNAL': 0}


def unescape(s):
    return re.sub(r'\\(.)', lambda m: ESCAPES.get(m.group(1), m.group(1)), s)


def parse_args(text):
    m = IDENT.match(text)
    if not m:
        raise ValueError('identifier expected')
    ident = m.group(1)
    pos = m.end()
    strs = []
    while pos < len(text):
        m = STRING.match(text, pos)
        if not m:
            raise ValueError('string literal expected near "%s"' % text[pos:pos + 20])
        strs.append(unescape(m.group(1)))
        pos = m.end()
    return ident, strs


class Registry:
    def __init__(self):
        self.params = {}
        self.subs = {}
        self.internal = {}
        self.errors = []

    def error(self, where, msg):
        self.errors.append('%s: %s' % (where, msg))

    def add(self, kind, ident, strs, where, rel, line):
        if len(strs) != NSTR[kind]:
            self.error(where, '%s needs %d string arguments, found %d' % (kind, NSTR[kind], len(strs)))
            return
        if not NAME_OK.match(ident):
            self.error(where, 'invalid name %s' % ident)
            return
        if kind == 'DG_PARAM_INTERNAL':
            if ident in self.internal:
                self.error(where, 'duplicate %s (first at %s)' % (ident, self.internal[ident]))
            self.internal[ident] = where
            return
        if kind == 'DG_PARAM':
            syntax, dflt, desc, example = strs
            key = ident
            rec = dict(name=ident, syntax=syntax, dflt=dflt, desc=desc, example=example,
                       file=rel, line=line, subs=[])
            table = self.params
        else:
            sub, syntax, dflt, desc, example = strs
            if not re.match(r'^-?[A-Za-z0-9][A-Za-z0-9_.-]*$', sub):
                self.error(where, 'invalid sub-option name %s' % sub)
                return
            key = (ident, sub)
            rec = dict(name=sub, parent=ident, syntax=syntax, dflt=dflt, desc=desc,
                       example=example, file=rel, line=line)
            table = self.subs
        if key in table:
            self.error(where, 'duplicate %s (first at %s:%d)' % (key, table[key]['file'], table[key]['line']))
            return
        for field, val in (('syntax', syntax), ('default', dflt), ('description', desc), ('example', example)):
            if not val.strip():
                self.error(where, '%s of %s is empty' % (field, key))
                return
        if len(desc) > MAX_DESC:
            self.error(where, 'description of %s has %d characters, maximum is %d' % (key, len(desc), MAX_DESC))
        if not example.startswith(ident + '='):
            self.error(where, 'example of %s must start with %s=' % (key, ident))
        table[key] = rec

    def finish(self):
        for (parent, sub), rec in self.subs.items():
            if parent not in self.params:
                self.error('%s:%d' % (rec['file'], rec['line']), 'sub-option %s of unknown parameter %s' % (sub, parent))
            else:
                self.params[parent]['subs'].append(rec)
        for name in self.internal:
            if name in self.params:
                self.error(self.internal[name], '%s is declared as public and internal' % name)
        for rec in self.params.values():
            rec['subs'].sort(key=lambda r: r['name'])


def source_files(root):
    base = os.path.join(root, 'delegate')
    for dirpath, dirnames, filenames in os.walk(base):
        dirnames.sort()
        for fn in sorted(filenames):
            if fn.endswith('.cpp'):
                yield os.path.join(dirpath, fn)


def load(root):
    reg = Registry()
    for path in source_files(root):
        rel = os.path.relpath(path, root)
        with open(path, 'rb') as f:
            text = f.read().decode('utf-8', 'replace')
        if 'DG_PARAM' not in text:
            continue
        for no, line in enumerate(text.split('\n'), 1):
            m = MACRO.match(line)
            if not m:
                continue
            where = '%s:%d' % (rel, no)
            try:
                ident, strs = parse_args(m.group(2))
            except ValueError as e:
                reg.error(where, 'syntax error in %s: %s' % (m.group(1), e))
                continue
            reg.add(m.group(1), ident, strs, where, rel, no)
    reg.finish()
    return reg


def cstr(s):
    return '"' + s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n') + '"'


def table_source(reg):
    out = ['// Generated by tools/gen-params.py. Do not edit.',
           '#include "dgparam.h"', '']
    names = sorted(reg.params)
    for name in names:
        subs = reg.params[name]['subs']
        if subs:
            out.append('static const DgParamSub subs_%s[] = {' % name)
            for s in subs:
                out.append('  {%s, %s, %s, %s, %s},' % tuple(cstr(s[k]) for k in ('name', 'syntax', 'dflt', 'desc', 'example')))
            out.append('};')
    out.append('')
    out.append('const DgParam dg_params[] = {')
    for name in names:
        p = reg.params[name]
        subs = ('subs_' + name) if p['subs'] else '0'
        out.append('  {%s, %s, %s, %s, %s, %s, %d, %s, %d},' % (
            cstr(name), cstr(p['syntax']), cstr(p['dflt']), cstr(p['desc']), cstr(p['example']),
            cstr(p['file']), p['line'], subs, len(p['subs'])))
    out.append('};')
    out.append('const int dg_params_count = %d;' % len(names))
    return '\n'.join(out) + '\n'


def cell(s):
    return s.replace('|', '\\|')


def markdown(reg):
    out = ['> Generated file. Renew with `cmake --build <dir> --target param-docs`.', '',
           '# DeleGate parameter reference', '']
    for name in sorted(reg.params):
        p = reg.params[name]
        out += ['## ' + name, '',
                'Syntax: `%s`' % p['syntax'], '',
                'Default: `%s`' % p['dflt'], '',
                p['desc'], '',
                '```', p['example'], '```', '']
        if p['subs']:
            out += ['| Option | Syntax | Default | Description | Example |',
                    '|---|---|---|---|---|']
            for s in p['subs']:
                out.append('| %s |' % ' | '.join([
                    '`%s`' % cell(s['name']), '`%s`' % cell(s['syntax']), '`%s`' % cell(s['dflt']),
                    cell(s['desc']), '`%s`' % cell(s['example'])]))
            out.append('')
        out += ['Source: `%s`' % p['file'], '']
    return '\n'.join(out)


def write_if_changed(path, text):
    try:
        with open(path, encoding='utf-8') as f:
            if f.read() == text:
                return False
    except FileNotFoundError:
        pass
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(text)
    return True


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--root', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    ap.add_argument('--table')
    ap.add_argument('--md')
    args = ap.parse_args()
    root = os.path.abspath(args.root)
    reg = load(root)
    if reg.errors:
        for e in reg.errors:
            print(e, file=sys.stderr)
        return 1
    if args.table:
        write_if_changed(args.table, table_source(reg))
    if args.md:
        write_if_changed(args.md, markdown(reg))
    return 0


if __name__ == '__main__':
    sys.exit(main())
