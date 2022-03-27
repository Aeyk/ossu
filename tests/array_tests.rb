#!/usr/bin/env ruby

require 'ffi'

module OSSU
  extend FFI::Library
  ffi_lib "build/libossu-arrays.so"
  attach_function :make_array, [ :size_t ], :pointer
  attach_function :print_array, [ :pointer ], :void
  attach_function :destroy_array, [ :pointer ], :void
  attach_function :at, [ :pointer, :size_t ], :size_t
  attach_function :size, [ :pointer ], :size_t
  attach_function :capacity, [ :pointer ], :size_t
  attach_function :is_empty, [ :pointer ], :bool
  attach_function :prepend, [ :pointer, :size_t ], :pointer
  attach_function :append, [ :pointer, :size_t ], :pointer
  attach_function :pop, [ :pointer ], :pointer
  attach_function :shift, [ :pointer ], :pointer
  attach_function :insert, [  :pointer, :size_t, :size_t ], :pointer
  attach_function :delete, [ :pointer, :size_t ], :pointer
end


def log_like_c(arr)
  fill = 0
  size = 0
  s = "[INFO] ruby_array			 "
  arr.each_with_index {|x, i|
    s += "buffer[#{i}]: #{x} "
  }
  s += "size: #{arr.length} fill: NUL"
  puts s
  return s
end


OSSU.destroy_array(OSSU.make_array(2))
r = []
c = OSSU.make_array(2)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)
OSSU.pop(c)

8.times {|x|
  OSSU.prepend(c, x+1)
  r.prepend(x)
}
log_like_c r

OSSU.destroy_array(c)
c = OSSU.make_array(2)
r = []
8.times {|x|
  OSSU.append(c, x+1)
  r.append(x)
}
log_like_c r

OSSU.destroy_array(c)
c = OSSU.make_array(2)
r = []
8.times {|x|
  OSSU.append(c, x+1)
  r.append(x)
}
log_like_c r


# c = OSSU.make_array(1)
# r = []
# 8.times {|x|
#   OSSU.prepend(c, x + 1)
#   r.prepend(x)
# }
# log_like_c r

# 8.times {|x|
#   OSSU.shift(c)
#   r.shift
# }

# 8.times {|x|
#   OSSU.append(c, x+1)
#   r.append(x)
# }
# log_like_c r

# 8.times {|x|
#   OSSU.pop(c)
#   r.pop
# }
# log_like_c r


# 10.times {|x|
#   OSSU.prepend(c, 128);
#   OSSU.pop(c);
# }

# 8.times { |x|
#   OSSU.prepend(c, 255);
# }
# 8.times { |x|
#   OSSU.pop(c);
# }

# 8.times { |x|
#   OSSU.prepend(c, 2 ** x);
#   OSSU.pop(c);
# }

# 4.times {|x|
#   OSSU.prepend(c, 2 ** x);
# }

# 4.times {|x|
#   OSSU.shift(c);
# }

# 4.times {|x|
#   OSSU.shift(c);
# }

# 4.times {|x|
#   OSSU.prepend(c, x*2);
# }

# 4.times {|x|
#   OSSU.pop(c);
# }

# 4.times{|x|
#   OSSU.append(c, 1+x*4);
# }

# 4.times{|x|
#   OSSU.prepend(c, 1+x*4);
# }

# 4.times {|x|
#   OSSU.at(c, x);
# }

# 4.times {|x|
#   OSSU.pop(c);
# }

# c = OSSU.make_array(1)
# r = []
# # 4.times {|x|
# #   OSSU.insert(c, x * 8, x);
# #   r.insert(x * 8, x)
# # }

# c = OSSU.make_array(1)
# r = []
# 4.times{|x|
#   OSSU.prepend(c, x);
#   r.prepend(x)
# }
# log_like_c r
# OSSU.print_array(c)


# r = []
# c = OSSU.make_array(2)
# 4.times{|x|
#   OSSU.append(c, x);
#   r.append(x)
# }


# log_like_c r
# OSSU.print_array(c)

