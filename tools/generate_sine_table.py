import os
import math

def write_prolog( dest_file, data_type, resolution ):
    dest_file.write("#include <array>\n\n")
    dest_file.write("namespace ysp\n{\nnamespace detail\n{\n")
    dest_file.write("\nconst std::array< " + data_type + ", " + str(resolution) +" > k_sine_table{\n")

def write_epilog( dest_file ):
	dest_file.write("};\n")
	dest_file.write("} // namespace detail\n")
	dest_file.write("} // namespace ysp\n")
	dest_file.write("\n")

def write_file( dest_filename, data_type, resolution, max_wave_length ):
    with open( dest_filename, 'w' ) as dest_file:
    	write_prolog( dest_file, data_type, resolution )

    	for i in range( resolution ):
    		value = math.sin(  i / resolution * max_wave_length )
    		dest_file.write( "    " + str(value) + "f" )
    		if i < resolution - 1:
    			dest_file.write(",")
    		dest_file.write("\n")

    	write_epilog( dest_file )

if __name__ == "__main__":
    
    script_dir = os.path.dirname( os.path.realpath( __file__ ) )
    dest = "../src/ysp/math/sine_table.h"
    dest = os.path.join( script_dir, dest )
    data_type = "float"
    resolution = 1024
    max_wave_length = 2 * math.pi

    write_file( dest, data_type, resolution, max_wave_length )
