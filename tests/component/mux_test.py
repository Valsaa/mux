import os
import pathlib
import pytest
import subprocess
import logging
import typing

DEFAULT_TIMEOUT = 5
logger = logging.getLogger(__name__)

@pytest.fixture
def root_dir() -> pathlib.PurePath:
    return pathlib.PosixPath(os.path.dirname(os.path.abspath(__file__)), "..","..").resolve()

@pytest.fixture
def mux_path(root_dir: pathlib.PurePath) -> pathlib.PurePath:
    return pathlib.PurePath(root_dir, "build/bin/mux")

@pytest.fixture
def mux(bin_path: pathlib.PurePath, request: pytest.FixtureRequest) -> subprocess.Popen[bytes]:
    return subprocess.Popen(
        [bin_path] + request.param,
        stdout = subprocess.PIPE
    )
     
@pytest.mark.parametrize("params", [
    ["--help"], 
    ["-h"], 
    ["-h", "-l", "8000"],
    ["-h", "127.0.0.1", "8000"]
    ])
def test_help(mux_path: pathlib.PurePath, params: typing.List[str]):    
    mux = subprocess.Popen([mux_path] + params, stdout = subprocess.PIPE)
    try:
        stdout, stderr = mux.communicate(timeout=DEFAULT_TIMEOUT)
        assert b"Usage" in stdout
        assert stderr == None     
        assert mux.returncode == 0
    except subprocess.TimeoutExpired:
        mux.kill()
        
@pytest.mark.parametrize("params", [
    ["foobar"],
    [""]
    ])
def test_wrong_param(mux_path: pathlib.PurePath, params: typing.List[str]):    
    mux = subprocess.Popen([mux_path] + params, stdout = subprocess.PIPE)
    try:
        stdout, stderr = mux.communicate(timeout=DEFAULT_TIMEOUT)
        assert b"Usage" in stdout
        assert stderr == None     
        assert mux.returncode == 1
    except subprocess.TimeoutExpired:
        mux.kill()
