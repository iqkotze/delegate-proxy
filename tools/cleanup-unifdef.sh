#!/usr/bin/env bash
# Removes non-Linux conditional code from all .c/.h files under delegate/ (except delegate/pds/) with unifdef.
# Usage: tools/cleanup-unifdef.sh [--dry-run]   (--dry-run only lists the files that would change)
set -euo pipefail

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
dry=0
case "${1:-}" in
	--dry-run) dry=1 ;;
	"") ;;
	*) echo "usage: cleanup-unifdef.sh [--dry-run]" >&2; exit 2 ;;
esac
command -v unifdef >/dev/null || { echo "unifdef not found (apt-get install unifdef)" >&2; exit 2; }

macros=(
	-U_MSC_VER -UUNDER_CE -U__CYGWIN__ -U__MINGW32__ -U__EMX__ -UOS2EMX
	-U__osf__ -U__hpux -U__hpux__ -Uhpux -U_AIX -Usgi -U_nec_ews -Unews
	-U__bsdi__ -UNeXT -Uultrix -U__KURO_BOX__ -USOLARIS25 -UMSWIN -U_WIN32 -UWIN32
	-U__APPLE__ -U__FreeBSD__ -U__NetBSD__ -U__OpenBSD__ -U__DragonFly__
	-Usun -U__sun -U__sun__ -U__SVR4 -U__aarch64__ -U__arm__ -U__i386__
	-D__linux__ -D__x86_64__ -D__amd64__
	-USOLARIS2 -U__sony_news -Usony_news -U_SYSTYPE_SYSV -U__Free_BSD__
	-U_BSDI_VERSION -Uvax -Umips -Usparc -U__hppa__ -UWIN32_FCLOSE_TEST
)

changed=0
failed=()
while IFS= read -r -d '' f; do
	rc=0
	if [ "$dry" -eq 1 ]; then
		unifdef "${macros[@]}" "$f" >/dev/null || rc=$?
	else
		unifdef -m "${macros[@]}" "$f" || rc=$?
	fi
	case "$rc" in
		0) ;;
		1) changed=$((changed + 1)); echo "$f" ;;
		*) failed+=("$f") ;;
	esac
done < <(find "$root/delegate" -path "$root/delegate/pds" -prune -o -type f \( -name '*.c' -o -name '*.h' \) -print0 | sort -z)

echo "changed: $changed" >&2
if [ "${#failed[@]}" -gt 0 ]; then
	echo "unifdef failed (exit 2) for ${#failed[@]} files" >&2
	printf '  %s\n' "${failed[@]}" >&2
fi
