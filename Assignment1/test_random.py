import base64
import os
import random
import string
import subprocess
import tempfile

def run_command(input_data, args):
    with tempfile.NamedTemporaryFile(delete=False) as f:
        f.write(input_data)
        f.flush()
        process = subprocess.run(
            ["./ascii85"] + args,
            stdin=open(f.name, 'rb'),
            capture_output=True
        )
    os.unlink(f.name)
    return process

def test_encode_decode_buffered():
    for _ in range(100):
        length = random.randint(0, 1000)
        data = os.urandom(length)
        expected = base64.a85encode(data)
        
        # Test encoding
        result = run_command(data, ["-e"])
        assert result.returncode == 0
        assert result.stdout == expected
        
        # Test decoding
        result = run_command(expected, ["-d"])
        assert result.returncode == 0
        assert result.stdout == data

def test_encode_decode_streaming():
    for _ in range(100):
        length = random.randint(0, 1000)
        data = os.urandom(length)
        expected = base64.a85encode(data)
        
        # Test encoding
        result = run_command(data, ["-e", "--stream"])
        assert result.returncode == 0
        assert result.stdout == expected
        
        # Test decoding
        result = run_command(expected, ["-d", "--stream"])
        assert result.returncode == 0
        assert result.stdout == data

def test_invalid_decode():
    for _ in range(100):
        length = random.randint(1, 100)
        invalid = ''.join(random.choice(string.ascii_letters + string.digits + string.punctuation) for _ in range(length))
        if all(33 <= ord(c) <= 117 for c in invalid) and len(invalid) % 5 == 0:
            continue  # Skip valid inputs
        result = run_command(invalid.encode(), ["-d"])
        assert result.returncode != 0

if __name__ == "__main__":
    test_encode_decode_buffered()
    test_encode_decode_streaming()
    test_invalid_decode()
    print("All random tests passed!")