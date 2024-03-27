import os
import pathlib
import pytest
import subprocess
import logging

DEFAULT_TIMEOUT = 5
logger = logging.getLogger(__name__)

@pytest.fixture
def root_dir() -> pathlib.PurePath:
    return pathlib.PosixPath(os.path.dirname(os.path.abspath(__file__)), "..","..").resolve()

@pytest.fixture
def bin_path(root_dir: pathlib.PurePath) -> pathlib.PurePath:
    return pathlib.PurePath(root_dir, "build/bin/mux")

@pytest.fixture
def mux(bin_path: pathlib.PurePath, request: pytest.FixtureRequest) -> subprocess.Popen[bytes]:
    return subprocess.Popen(
        [bin_path] + request.param,
        stdout = subprocess.PIPE
    )
     
@pytest.mark.parametrize("mux", [["--help"], ["-h"]], indirect=True)
def test_help(mux: subprocess.Popen[bytes]):
    try:
        stdout, stderr = mux.communicate(timeout=DEFAULT_TIMEOUT)
        assert stdout != None
        assert stderr == None     
        assert mux.returncode == 0
    except subprocess.TimeoutExpired:
        mux.kill()
        