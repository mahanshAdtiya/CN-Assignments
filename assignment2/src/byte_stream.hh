
#ifndef SPONGE_LIBSPONGE_BYTE_STREAM_HH
#define SPONGE_LIBSPONGE_BYTE_STREAM_HH

#include <string>
#include <deque>

using namespace std;

class ByteStream {

  private:
      deque<char> buffer_; 
      size_t capacity_;        
      bool input_ended_;        
      size_t bytes_written_;    
      size_t bytes_read_;       
      bool _error;              

  public:
      ByteStream(const size_t capa);

      // Writes the given data to the input side of the byte stream.
      // Returns the number of bytes written.
      size_t write(const string& data);

      // Returns the remaining storage capacity.
      size_t remaining_capacity() const;

      // Ends the input side of the byte stream.
      void end_input();

      void set_error() { _error = true; }

      // Peeks at the next 'len' bytes in the output side without removing them.
      string peek_output(const size_t len) const;

      // Pops 'len' bytes from the output side.
      void pop_output(const size_t len);

      // Reads 'len' bytes from the output side.
      string read(const size_t len);

      // Checks if the input side has ended.
      bool input_ended() const;

      bool error() const { return _error; }

      // Returns the current buffer size (unconsumed bytes).
      size_t buffer_size() const;

      // Checks if the buffer is empty.
      bool buffer_empty() const;

      // Checks if the end of the stream (EOF) has been reached.
      bool eof() const;

      // Returns the total bytes written to the stream.
      size_t bytes_written() const;

      // Returns the total bytes read from the stream.
      size_t bytes_read() const;

      // Checks if an error occurred during stream operations.
      bool has_error() const;

};

#endif // BYTE_STREAM_HH
