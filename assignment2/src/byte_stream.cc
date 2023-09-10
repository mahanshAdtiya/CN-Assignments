#include "byte_stream.hh"
#include <algorithm>

using namespace std;

ByteStream::ByteStream(const size_t capa) : capacity_(capa), input_ended_(false), bytes_written_(0), bytes_read_(0), _error(false) {}

size_t ByteStream::write(const string& data) {
  if (_error || input_ended_) {
      _error = true; 
      return 0;     
  }

  size_t bytes_written = 0;
  for(int i = 0; i < data.length(); i++){
    if (buffer_.size() < capacity_) {
          buffer_.push_back(data[i]);
          bytes_written++;
          bytes_written_++;
      } else {
          break; 
      }
  }
  
  return bytes_written;
}

size_t ByteStream::remaining_capacity() const {

  return (buffer_.size() <= capacity_) ? capacity_ - buffer_.size() : 0;
}

void ByteStream::end_input() {
  input_ended_ = true;
}

string ByteStream::peek_output(const size_t len) const {
  string output;
  for (size_t i = 0; i < len && i < buffer_.size(); ++i) {
      output += buffer_[i];
  }
  return output;
}

void ByteStream::pop_output(const size_t len) {
  for (size_t i = 0; i < len && !buffer_.empty(); ++i) {
      buffer_.pop_front();
      bytes_read_++;
  }
}

string ByteStream::read(const size_t len) {
  string output = peek_output(len);
  pop_output(len);
  return output;
}

bool ByteStream::input_ended() const {
  return input_ended_;
}

size_t ByteStream::buffer_size() const {
  return buffer_.size();
}

bool ByteStream::buffer_empty() const {
  return buffer_.empty();
}

bool ByteStream::eof() const { // not sure yet
  return input_ended_ && buffer_.empty();
}

size_t ByteStream::bytes_written() const {
  return bytes_written_;
}

size_t ByteStream::bytes_read() const {
  return bytes_read_;
}

bool ByteStream::has_error() const {
  return _error;
}
