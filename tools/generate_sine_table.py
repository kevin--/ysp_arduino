import os
import math

class dotdict(dict):
    """dot.notation access to dictionary attributes"""
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__

def write_prolog( dest_file, config ):
    dest_file.write("#pragma once\n\n")
    dest_file.write("#include <array>\n\n")
    dest_file.write("namespace ysp\n{\nnamespace detail\n{\n")
    dest_file.write("\nconst std::array< " + config.data_type + ", " + str(config.resolution) +" > k_")
    dest_file.write(config.name)
    dest_file.write("{\n")

def write_epilog( dest_file ):
    dest_file.write("};\n")
    dest_file.write("} // namespace detail\n")
    dest_file.write("} // namespace ysp\n")
    dest_file.write("\n")

def write_file( config ):

    script_dir = os.path.dirname( os.path.realpath( __file__ ) )
    dest_filename = "../src/ysp/math/" + config.name + ".h"
    dest_filename = os.path.join( script_dir, dest_filename )

    with open( dest_filename, 'w' ) as dest_file:
        write_prolog( dest_file, config )

        for i in range( config.resolution ):

            frac = i / config.resolution
            if config.end_on:
                frac = i / (config.resolution - 1)
                
            value = math.sin( frac * config.max_wave_length )

            dest_file.write( "    " + str(value) + "f" )
            if i < config.resolution - 1:
                dest_file.write(",")
            dest_file.write("\n")

        write_epilog( dest_file )

if __name__ == "__main__":

    preset_full_wave = dotdict()
    preset_full_wave.data_type = "float"
    preset_full_wave.end_on = False
    preset_full_wave.resolution = 1024
    preset_full_wave.max_wave_length = 2 * math.pi
    preset_full_wave.name = "sine_table_full"

    preset_quarter_wave = dotdict()
    preset_quarter_wave.data_type = "float"
    preset_quarter_wave.end_on = True
    preset_quarter_wave.resolution = 256
    preset_quarter_wave.max_wave_length = math.pi / 2
    preset_quarter_wave.name = "sine_table_quarter"

    write_file( preset_quarter_wave )
