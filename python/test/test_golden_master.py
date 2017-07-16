import os
import cStringIO as io

from mock import patch

import make_golden_master

GOLDEN_MASTER = "golden-master.out"


def write_golden_master(path):
    with open(path, "w") as out:
        run_golden_master(out)


def run_golden_master(out):
    with patch("sys.stdout", out):
        make_golden_master.make()


def test_golden_master():
    if not os.path.exists(GOLDEN_MASTER):
        write_golden_master(GOLDEN_MASTER)

    golden_master_content = open(GOLDEN_MASTER).read()

    out = io.StringIO()
    run_golden_master(out)
    assert out.getvalue() == golden_master_content
