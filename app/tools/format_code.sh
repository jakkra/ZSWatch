astyle \
--options=tools/astyle.cfg \
--suffix=none \
--verbose \
--errors-to-stdout \
--recursive src/*.c,*.h \
--recursive drivers/*.c,*.h \
--exclude=src/images \
--exclude=src/ext_drivers \
--exclude=drivers/input \
--exclude=drivers/sensor \
--exclude=src/applications/2048/2048_lib \
$1 $2 $3 # addtional args such as --dry-run etc.