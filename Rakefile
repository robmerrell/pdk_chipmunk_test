require "rake"
 
desc "A quick and dirty build, not suitable for large projects."
task :build do
  # generate the compiler and linker flags
  flags = [
    "-Wno-write-strings",
    "-g",
    "-I/opt/PalmPDK/include",
    "-I/opt/PalmPDK/include/SDL",
    "-L/opt/PalmPDK/host/lib",
    "-framework cocoa",
    "-arch i386",
    "-Lsrc/chipmunk/lib",
    "-lchipmunk",
    "-lSDL",
    "-lSDLmain",
    "-lSDL_image",
    "-lpdl"
  ]
  
  # get a list of cpp files to compile
  files = Dir.glob("src/**/*.cpp")
  
  output_name = "main"
  
  # compile the files
  compile_cmd = "g++ #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
  puts compile_cmd
  system(compile_cmd)
end

desc "Build the chipmunk test against for the device"
task :build_device do
  # generate the compiler and linker flags
  flags = [
    "-mcpu=cortex-a8",
    "-mfpu=neon",
    "-mfloat-abi=softfp",
    "--sysroot=/opt/PalmPDK/arm-gcc/sysroot",
    "-L/opt/PalmPDK/device/lib -Wl,--allow-shlib-undefined",
    "-I/opt/PalmPDK/include",
    "-I/opt/PalmPDK/include/SDL",
    "-Lsrc/chipmunk/lib/device",
    "-lchipmunk",
    "-lSDL",
    "-lSDLmain",
    "-lSDL_image",
    "-lpdl"
  ]
  
  # get a list of cpp files to compile
  files = Dir.glob("src/**/*.cpp")
  
  output_name = "main"
  
  # compile the files
  compile_cmd = "/opt/PalmPDK/arm-gcc/bin/arm-none-linux-gnueabi-gcc #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
  puts compile_cmd
  system(compile_cmd)
end
