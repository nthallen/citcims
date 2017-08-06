#! /bin/sh
function nl_error {
  echo "mv_ext.sh: $*" >&2
  exit 1
}
analdir=$1
[ -n "$analdir" ] || nl_error "Must specify the analysis directory"
[ -d "$analdir" ] || nl_error "First argument must be a directory"
[ -f "$analdir/UPeng_1.csv" ] ||
  nl_error "Source file $analdir/UPeng_1.csv not found"
mv $analdir/UPeng_1.csv $analdir/UserPkts.csv
echo "mv_ext.sh: Renamed UPeng_1.csv to UserPkts.csv"

