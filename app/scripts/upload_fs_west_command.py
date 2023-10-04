from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output
from create_resource_fs import create_fs_image
from rtt_flash_loader import run_loader
import sys

class UploadFsWestCommand(WestCommand):

    def __init__(self):
        super().__init__(
            'upload_fs',
            'Upload the LVGL filesystem to external SPI Flash',
            '''Use to upload files to the external SPI flash.''')

    def do_add_parser(self, parser_adder):

        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        parser.add_argument('--read_file', type=str, help='If set dump flash to this filename')
        return parser

    def do_run(self, args, unknown_args):
        log.inf('Creating image')
        img_filename = "lvgl_resources"
        img_size = 2 *1024 * 1024
        block_size = 4096
        read_size = 16
        prog_size = 16
        name_max = 255
        file_max = 0
        attr_max = 0
        source_dir = "../src/images/binaries/"
        disk_version = "2.0"
        filename = "lvgl_resources"
        if (args.read_file):
            filename = args.read_file
        if args.read_file is None:
            create_fs_image(img_filename, img_size, block_size, read_size, prog_size, name_max, file_max, attr_max, source_dir, disk_version)
        sys.exit(run_loader("nRF5340_XXAA", filename, args.read_file))
