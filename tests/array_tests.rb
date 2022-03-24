#!/usr/bin/env ruby

require 'ffi'

module OSSU
  extend FFI::Library
  ffi_lib "./libossu-arrays.so"
  attach_function :make_vector, [ :size_t ], :pointer
  attach_function :destroy_vector, [ :pointer ], :void
  attach_function :at, [ :size_t ], :size_t
  attach_function :size, [ :pointer ], :size_t
  attach_function :capacity, [ :pointer ], :size_t
  attach_function :is_empty, [ :pointer ], :bool
  attach_function :push, [ :pointer, :size_t ], :pointer
  attach_function :push_tail, [ :pointer, :size_t ], :pointer
  attach_function :pop, [ :pointer ], :pointer
  attach_function :pop_head, [ :pointer ], :pointer
  attach_function :insert, [ :pointer ], :pointer
  attach_function :delete, [ :pointer ], :pointer

end

c_vec = OSSU.make_vector(10)
