#!/usr/bin/env ruby

require 'ffi'

module OSSU
  extend FFI::Library
  ffi_lib 'c'
  attach_function :puts, [ :string ], :int
end

OSSU.puts 'Hello, World using libc!'
