#  ASCII85 Decoder and Encoder 
Implementation of the ASCII85 decoder and encoder  
  
## Author  
Mobina Ahmadimasoud, group 24.B83-mm  
## Contacts  
st067173@student.spbu.ru    
  
## Description  
The ASCII85 (base85) decoder and encoder are implemented  
## Build
make
## Usage 
```
$ ascii85    # reads bytes from STDIN and outputs ASCII85 to STDOUT
$ ascii85 -e # reads bytes from STDIN and outputs ASCII85 to STDOUT
$ ascii85 -d # reads ASCII85 from STDIN and outputs bytes to STDOUT; exits with a non-0 code on error
```
# Run Unit Tests
./test_ascii85

# Run Random Data Tests
python3 ../test_random.py