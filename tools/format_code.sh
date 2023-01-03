astyle \
--options=tools/astyle.cfg \
--suffix=none \
--verbose \
--errors-to-stdout \
--recursive src/*.c,*.h \
--recursive drivers/*.c,*.h \
--exclude=src/images \
$1 $2 $3 # addtional args such as --dry-run etc.