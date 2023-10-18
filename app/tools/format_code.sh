astyle \
--options=tools/astyle.cfg \
--recursive src/*.c,*.h \
--recursive drivers/*.c,*.h \
$1 $2 $3 # addtional args such as --dry-run etc.