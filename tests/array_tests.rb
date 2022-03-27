#!/usr/bin/env ruby

require 'ffi'

module OSSU
  extend FFI::Library
  ffi_lib "build/libossu-arrays.so"
  attach_function :make_vector, [ :size_t ], :pointer
  attach_function :destroy_vector, [ :pointer ], :void
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
  s = "[INFO] ruby_array			 "
  arr.each_with_index {|x, i|
    s += "buffer[#{i}]: #{x} "
  }
  puts s
  return s
end


# OSSU.destroy_vector(OSSU.make_vector(2))
# r_vec = []
# c_vec = OSSU.make_vector(2)
# OSSU.pop(c_vec)
# OSSU.pop(c_vec)
# OSSU.pop(c_vec)
# 8.times {|x|
#   OSSU.prepend(c_vec, x+1)
#   r_vec.prepend(x)
# }
# log_like_c r_vec

# OSSU.destroy_vector(c_vec)
# c_vec = OSSU.make_vector(2)
# r_vec = []
# 8.times {|x|
#   OSSU.append(c_vec, x+1)
#   r_vec.append(x)
# }
# log_like_c r_vec

# OSSU.destroy_vector(c_vec)
# c_vec = OSSU.make_vector(2)
# r_vec = []
# 8.times {|x|
#   OSSU.append(c_vec, x+1)
#   r_vec.append(x)
# }
# log_like_c r_vec


c_vec = OSSU.make_vector(1)
r_vec = []
8.times {|x|
  OSSU.prepend(c_vec, x + 1)
  r_vec.prepend(x)
}
log_like_c r_vec

8.times {|x|
  OSSU.shift(c_vec)
  r_vec.shift
}

8.times {|x|
  OSSU.append(c_vec, x+1)
  r_vec.append(x)
}
log_like_c r_vec

8.times {|x|
  OSSU.pop(c_vec)
  r_vec.pop
}
log_like_c r_vec


# 10.times {|x|
#   OSSU.prepend(c_vec, 128);
#   OSSU.pop(c_vec);
# }

# 8.times { |x|
#   OSSU.prepend(c_vec, 255);
# }
# 8.times { |x|
#   OSSU.pop(c_vec);
# }

# 8.times { |x|
#   OSSU.prepend(c_vec, 2 ** x);
#   OSSU.pop(c_vec);
# }

# 4.times {|x|
#   OSSU.prepend(c_vec, 2 ** x);
# }

# 4.times {|x|
#   OSSU.shift(c_vec);
# }

# 4.times {|x|
#   OSSU.shift(c_vec);
# }

# 4.times {|x|
#   OSSU.prepend(c_vec, x*2);
# }

# 4.times {|x|
#   OSSU.pop(c_vec);
# }

# 4.times{|x|
#   OSSU.append(c_vec, 1+x*4);
# }

# 4.times{|x|
#   OSSU.prepend(c_vec, 1+x*4);
# }

# 4.times {|x|
#   OSSU.at(c_vec, x);
# }

# 4.times {|x|
#   OSSU.pop(c_vec);
# }

# 4.times {|x|
#   OSSU.insert(c_vec, x * 8, x);
# }


