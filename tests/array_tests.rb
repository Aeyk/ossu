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
  attach_function :push, [ :pointer, :size_t ], :pointer
  attach_function :push_tail, [ :pointer, :size_t ], :pointer
  attach_function :pop, [ :pointer ], :pointer
  attach_function :pop_head, [ :pointer ], :pointer
  attach_function :insert, [  :pointer, :size_t, :size_t ], :pointer
  attach_function :delete, [ :pointer, :size_t ], :pointer

end
OSSU.destroy_vector(OSSU.make_vector(2))
r_vec = []
c_vec = OSSU.make_vector(2)
8.times {|x|
  OSSU.push_tail(c_vec, x+1)
  r_vec << x
}

8.times {|x|
  OSSU.pop_head(c_vec)
  r_vec.unshift
}

8.times {|x|
  OSSU.push_tail(c_vec, x+1)
  r_vec.append(x)
}

8.times {|x|
  OSSU.pop(c_vec)
  r_vec.pop
}



# 10.times {|x|
#   OSSU.push(c_vec, 128);
#   OSSU.pop(c_vec);
# }

# 8.times { |x|
#   OSSU.push(c_vec, 255);
# }
# 8.times { |x|
#   OSSU.pop(c_vec);
# }

# 8.times { |x|
#   OSSU.push(c_vec, 2 ** x);
#   OSSU.pop(c_vec);
# }

# 4.times {|x|
#   OSSU.push(c_vec, 2 ** x);
# }

# 4.times {|x|
#   OSSU.pop_head(c_vec);
# }

# # 4.times {|x|
# #   OSSU.pop_head(c_vec);
# # }

# 4.times {|x|
#   OSSU.push(c_vec, x*2);
# }

# 4.times {|x|
#   OSSU.pop(c_vec);
# }

# 4.times{|x|
#   OSSU.push_tail(c_vec, 1+x*4);
# }

# 4.times{|x|
#   OSSU.push(c_vec, 1+x*4);
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


