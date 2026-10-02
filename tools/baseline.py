#!/usr/bin/env python3
"""Compares clang-tidy or cppcheck findings with a baseline of counts per file and check.

Usage: tools/baseline.py REPORT BASELINE [--root DIR] [--update] [--codequality FILE]
The report holds lines of the form FILE:LINE:COL: SEVERITY: MESSAGE [CHECK].
Exit code 1 if a count exceeds the baseline. --update rewrites the baseline.
"""
import argparse
import collections
import hashlib
import json
import os
import re
import sys

LINE = re.compile(r'^(/?[^\s:][^:]*):(\d+):(\d+): (warning|error|style|performance|portability|information): (.*) \[([\w.\-]+)\]$')
SEVERITY = {'error': 'major', 'warning': 'minor', 'style': 'info', 'performance': 'info',
            'portability': 'info', 'information': 'info'}


def read_findings(report, root):
    seen = {}
    with open(report, errors='replace') as f:
        for raw in f:
            m = LINE.match(raw.rstrip('\n'))
            if not m:
                continue
            path = os.path.normpath(os.path.join(root, m.group(1)))
            rel = os.path.relpath(path, root)
            if rel.startswith('..') or rel.startswith('build' + os.sep):
                continue
            key = (rel, int(m.group(2)), int(m.group(3)), m.group(6))
            seen[key] = (m.group(4), m.group(5))
    return seen


def count(findings):
    c = collections.Counter()
    for rel, _, _, check in findings:
        c[(rel, check)] += 1
    return c


def read_baseline(path):
    c = collections.Counter()
    if os.path.exists(path):
        with open(path) as f:
            for line in f:
                parts = line.rstrip('\n').split('\t')
                if len(parts) == 3:
                    c[(parts[1], parts[2])] = int(parts[0])
    return c


def write_baseline(path, c):
    with open(path, 'w') as f:
        for (rel, check), n in sorted(c.items()):
            f.write('%d\t%s\t%s\n' % (n, rel, check))


def write_codequality(path, findings):
    out = []
    for (rel, line, col, check), (sev, msg) in sorted(findings.items()):
        fp = hashlib.md5(('%s:%d:%d:%s:%s' % (rel, line, col, check, msg)).encode()).hexdigest()
        out.append({'description': msg, 'check_name': check, 'fingerprint': fp,
                    'severity': SEVERITY.get(sev, 'minor'),
                    'location': {'path': rel, 'lines': {'begin': line}}})
    with open(path, 'w') as f:
        json.dump(out, f)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('report')
    ap.add_argument('baseline')
    ap.add_argument('--root', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    ap.add_argument('--update', action='store_true')
    ap.add_argument('--codequality')
    a = ap.parse_args()
    root = os.path.abspath(a.root)

    findings = read_findings(a.report, root)
    cur = count(findings)
    if a.codequality:
        write_codequality(a.codequality, findings)
    if a.update:
        write_baseline(a.baseline, cur)
        print('baseline updated: %d findings in %d entries' % (sum(cur.values()), len(cur)))
        return 0

    base = read_baseline(a.baseline)
    new = [(k, n, base.get(k, 0)) for k, n in sorted(cur.items()) if n > base.get(k, 0)]
    print('findings %d, baseline %d' % (sum(cur.values()), sum(base.values())))
    for (rel, check), n, b in new:
        print('NEW %s %s (%d, baseline %d)' % (rel, check, n, b))
    return 1 if new else 0


if __name__ == '__main__':
    sys.exit(main())
