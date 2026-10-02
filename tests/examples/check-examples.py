#!/usr/bin/env python3
"""Checks that the examples in doc/examples use only documented parameters and have one-line comments.

Usage: tests/examples/check-examples.py [--root DIR]
"""
import argparse
import glob
import os
import re
import sys

LISTS = ('MAXIMA', 'TIMEOUT')


def reference(path):
    params = {}
    cur = None
    with open(path, encoding='utf-8') as f:
        for line in f:
            m = re.match(r'^## (\S+)$', line)
            if m:
                cur = m.group(1)
                params[cur] = set()
                continue
            m = re.match(r'^\| `([^`]+)` \|', line)
            if m and cur:
                params[cur].add(m.group(1))
    return params


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--root', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
    root = os.path.abspath(ap.parse_args().root)
    params = reference(os.path.join(root, 'doc', 'reference', 'parameters.md'))
    files = sorted(glob.glob(os.path.join(root, 'doc', 'examples', '*.conf')))
    problems = []
    if len(files) < 10:
        problems.append('fewer than 10 examples (%d)' % len(files))
    for path in files:
        name = os.path.basename(path)
        prev_comment = False
        for no, line in enumerate(open(path, encoding='utf-8'), 1):
            line = line.rstrip('\n')
            where = '%s:%d' % (name, no)
            if line.startswith('#'):
                if prev_comment:
                    problems.append('%s: comment longer than one line' % where)
                prev_comment = True
                continue
            prev_comment = False
            if not line or line.startswith('-'):
                continue
            m = re.match(r'^([A-Z][A-Z0-9_]*)=(.*)$', line)
            if not m:
                problems.append('%s: not a parameter or option: %s' % (where, line))
                continue
            key, value = m.groups()
            if key not in params:
                problems.append('%s: %s is not in the parameter reference' % (where, key))
            elif key in LISTS:
                for item in value.split(','):
                    if item.split(':')[0] not in params[key]:
                        problems.append('%s: %s option %s is not in the parameter reference' % (where, key, item))
            elif key == 'MOUNT':
                fields = value.strip('"').split()
                for opt in (fields[2].split(',') if len(fields) > 2 else []):
                    if opt.split('=')[0] not in params[key]:
                        problems.append('%s: MOUNT option %s is not in the parameter reference' % (where, opt))
    for p in problems:
        print(p, file=sys.stderr)
    print('examples: %d, problems: %d' % (len(files), len(problems)))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
