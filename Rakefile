require "rake"

# all tasks accept the following arguments:
# PRE
# PIXI
# MAC assumed

task :arch_settings do
  if ENV["PRE"]
    $arch_settings = "-mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp"
  elsif ENV["PIXI"]
    $arch_settings = "-mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp"
  else
    $arch_settings = "-framework cocoa -arch i386 -lSDLmain"
  end
end


# add a
FileList["src/chipmunk/**/*.c"].each do |src|
	file :build_chipmunk => src
end

desc "Build and create a static library of the Chipmunk physics engine"
file :build_chipmunk do
  flags = [
    "-Wno-write-strings",
    "-Ichipmunk/headers"
  ]
  
  # puts "blah"
  # build chipmunk
end


# desc "Build the Chipmunk physics engine"
# task :build_chipmunk => :arch_settings do
# 
# end
# 
# desc "Build the physics simulator"
# task :build => :build_chipmunk do
# 
# end
# 
# 
# # set up some simple file dependencies
# file "build/libchipmunk.a" do
#   puts "blah"
# end

 
# desc "A quick and dirty build, not suitable for large projects."
# task :build do
#   # generate the compiler and linker flags
#   flags = [
#     "-Wno-write-strings",
#     "-g",
#     "-I/opt/PalmPDK/include",
#     "-I/opt/PalmPDK/include/SDL",
#     "-L/opt/PalmPDK/host/lib",
#     "-framework cocoa",
#     "-arch i386",
#     "-Lsrc/chipmunk/lib",
#     "-lchipmunk",
#     "-lSDL",
#     "-lSDLmain",
#     "-lSDL_image",
#     "-lpdl"
#   ]
#   
#   # get a list of cpp files to compile
#   files = Dir.glob("src/**/*.cpp")
#   
#   output_name = "main"
#   
#   # compile the files
#   compile_cmd = "g++ #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
#   puts compile_cmd
#   system(compile_cmd)
# end
# # 
# desc "Build the chipmunk test against for the device"
# task :build_device do
#   # generate the compiler and linker flags
#   flags = [
#     "-mcpu=cortex-a8",
#     "-mfpu=neon",
#     "-mfloat-abi=softfp",
#     "--sysroot=/opt/PalmPDK/arm-gcc/sysroot",
#     "-L/opt/PalmPDK/device/lib -Wl,--allow-shlib-undefined",
#     "-I/opt/PalmPDK/include",
#     "-I/opt/PalmPDK/include/SDL",
#     "-Lsrc/chipmunk/lib/device",
#     "-lchipmunk",
#     "-lSDL",
#     "-lSDL_image",
#     "-lpdl"
#   ]
#   
#   # get a list of cpp files to compile
#   files = Dir.glob("src/**/*.cpp")
#   
#   output_name = "main"
#   
#   # compile the files
#   compile_cmd = "/opt/PalmPDK/arm-gcc/bin/arm-none-linux-gnueabi-gcc #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
#   puts compile_cmd
#   system(compile_cmd)
# end
# 
# desc "Copy the app to the device and run the jerk"
# task :run do
#   copy_bin = "scp -r -P 10022 main root@localhost:/media/internal/pdk_chipmunk"
#   puts copy_bin
#   system(copy_bin)
#   
#   copy_asset = "scp -r -P 10022 assets/ball.gif root@localhost:/media/internal/pdk_chipmunk/assets"
#   puts copy_asset
#   system(copy_asset)
#   
#   run_cmd = "novacom run file:///media/internal/pdk_chipmunk/main"
#   system(run_cmd)
# end
# 
# desc "Create and install a package to the device"
# task :pkg do
#   pdk_bin = "/opt/PalmPDK/bin"
#   
#   # copy the executable and asset file to the package dir
#   system("cp main chipmunk_test")
#   system("cp assets/ball.gif chipmunk_test/assets")
# 
#   puts "packaging..."
#   system("#{pdk_bin}/pdk-package chipmunk_test")
#   
#   puts "installing..."
#   system("#{pdk_bin}/pdk-install com.trackera.chipmunk-test_1.0.0_all.ipk")
# end
