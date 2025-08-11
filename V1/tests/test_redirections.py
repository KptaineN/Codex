import os
import subprocess
from pathlib import Path
import pytest

BIN = str(Path(__file__).resolve().parents[1] / 'minishell')

def run_ms(cmds: str):
    return subprocess.run(BIN, input=cmds.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def test_missing_input_file():
    proc = run_ms('cat < missing\nexit\n')
    assert b'missing' in proc.stderr
    assert proc.returncode == 1

def test_output_invalid_permission():
    os.makedirs('test_files', exist_ok=True)
    path = Path('test_files/invalid_permission')
    if path.exists():
        if path.is_file():
            path.unlink()
        else:
            os.rmdir(path)
    path.mkdir()
    os.chmod(path, 0o000)
    proc = run_ms('echo test > ./test_files/invalid_permission\nexit\n')
    assert (b'Permission denied' in proc.stderr) or (b'Is a directory' in proc.stderr)
    assert proc.returncode == 1
