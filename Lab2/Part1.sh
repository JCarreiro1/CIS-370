grep -E -o '^.*[\<].*[\>]' GLPv3
echo
grep -E -o '\b[A-Z][a-z]+' GLPv3
echo
grep -E -o 'https.*\/' GLPv3
echo
grep -E -o '^[0-9].*' GLPv3
echo
grep -E '^[A-Z]+(\W+[A-Z]+)+\W' GLPv3
