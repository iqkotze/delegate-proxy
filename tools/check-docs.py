#!/usr/bin/env python3
"""Checks relative links in the Markdown files and dashes and colons in the German running text.
Usage: tools/check-docs.py [--root DIR]   (exit code 1 on findings)"""
import argparse
import glob
import os
import re
import sys

PROSE = ['README.md', 'CLAUDE.md', 'doc/*.md', 'doc/examples/README.md', 'doc/legacy/README.md']
LINKS = PROSE + ['tools/README.md', 'ci/README.md', 'CHANGELOG.md']
LINK = re.compile(r'\[[^\]]*\]\(([^)\s]+)\)')


def files(root, patterns):
    found = set()
    for pat in patterns:
        found.update(glob.glob(os.path.join(root, pat)))
    return sorted(found)


def check_links(root, path, problems):
    in_fence = False
    for no, line in enumerate(open(path, encoding='utf-8'), 1):
        if line.startswith('```'):
            in_fence = not in_fence
        if in_fence:
            continue
        for target in LINK.findall(line):
            if re.match(r'^[a-z]+:', target) or target.startswith('#'):
                continue
            target = target.split('#')[0]
            if not os.path.exists(os.path.normpath(os.path.join(os.path.dirname(path), target))):
                problems.append('%s:%d dead link %s' % (os.path.relpath(path, root), no, target))


def prose(line):
    line = LINK.sub(lambda m: m.group(0)[:m.group(0).index('](')], line)
    line = re.sub(r'`[^`]*`', '', line)
    line = re.sub(r'https?://\S+', '', line)
    return line


def check_prose(root, path, problems):
    in_fence = False
    for no, line in enumerate(open(path, encoding='utf-8'), 1):
        if line.startswith('```'):
            in_fence = not in_fence
            continue
        if in_fence or line.startswith('    ') or line.lstrip().startswith('|'):
            continue
        text = prose(line)
        for bad, name in (('–', 'en dash'), ('—', 'em dash'), (':', 'colon'), (' - ', 'dash')):
            if bad in text:
                problems.append('%s:%d %s in "%s"' % (os.path.relpath(path, root), no, name, line.strip()[:80]))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--root', default=os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    root = os.path.abspath(ap.parse_args().root)
    problems = []
    for path in files(root, LINKS):
        check_links(root, path, problems)
    for path in files(root, PROSE):
        check_prose(root, path, problems)
    for p in problems:
        print(p)
    print('findings: %d' % len(problems))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
