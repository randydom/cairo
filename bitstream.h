
/*
// Copyright (c) 2009-2014 Joe Bertolami. All Right Reserved.
//
// bitstream.h
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice, this
//     list of conditions and the following disclaimer.
//
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Additional Information:
//
//   For more information, visit http://www.bertolami.com.
*/

#ifndef __EVX_BIT_STREAM_H__	
#define __EVX_BIT_STREAM_H__	

#include "base.h"

#define EVX_READ_BIT(source, bit)           (((source) >> (bit)) & 0x1)
#define EVX_WRITE_BIT(dest, bit, value)     (dest) = (((dest) & ~(0x1 << (bit))) | \
                                            (((value) & 0x1) << (bit)))
namespace evx {

class bit_stream 
{
    uint32 read_index;
    uint32 write_index;
    uint32 data_capacity;
    uint8 *data_store;

public:

    bit_stream();
    bit_stream(uint32 size);
    bit_stream(void *bytes, uint32 size);
    virtual ~bit_stream();

    uint8 *query_data() const;
    uint32 query_capacity() const;
    uint32 query_occupancy() const;
    uint32 query_byte_occupancy() const;
    uint32 resize_capacity(uint32 size_in_bits);

    evx_status assign(void *bytes, uint32 size);

    // seek will only adjust the read index. 
    // there is purposely no way to adjust the write index.
    void seek(uint32 offset);
    void clear();   
    void empty();  

    bool is_empty() const;
    bool is_full() const;

    evx_status write_byte(uint8 value);
    evx_status write_bit(uint8 value);
    evx_status write_bytes(void *data, uint32 count);
    evx_status write_bits(void *data, uint32 count);

    evx_status read_byte(void *data);
    evx_status read_bit(void *data);
    evx_status read_bytes(void *data, uint32 count);
    evx_status read_bits(void *data, uint32 count);

    evx_status peek_byte(void *data);
    evx_status peek_bit(void *data);
    evx_status peek_bytes(void *data, uint32 count);
    evx_status peek_bits(void *data, uint32 count);

private:
  
    EVX_DISABLE_COPY_AND_ASSIGN(bit_stream);
};

} // namespace evx

#endif // __EVX_BIT_STREAM_H__
