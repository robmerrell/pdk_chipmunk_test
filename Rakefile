require "rake"
require "fileutils"
 
$pdk_path = "/opt/PalmPDK"
 
task :arch_settings do
  if ENV["TARGET"] == "pre"
    $arch_settings = "-mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp"
    $cc = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-gcc"
    $gpp = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-g++"
    $ar = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ar"
    $ranlib = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ranlib"
  elsif ENV["TARGET"] == "pixi"
    $arch_settings = "-mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp"
    $cc = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-gcc"
    $gpp = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-g++"
    $ar = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ar"
    $ranlib = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ranlib"
  else
    $arch_settings = "-arch i386"
    $cc = "gcc"
    $gpp = "g++"
    $ar = "ar"
    $ranlib = "ranlib"
  end
end
 
 
desc "Create a static library for the Chipmunk physics engine TARGET=pre, pixi or host(mac); host is assumed if TARGET is not set"
file :build_chipmunk => :arch_settings do
  flags = [
    "-Wno-write-strings",
    "-Isrc/chipmunk/headers",
    "-std=gnu99",
    "-O3",
    "-DNDEBUG",
    "-ffast-math"
  ]
  
  # compile all of the files
  files = Dir.glob("src/chipmunk/**/*.c")
  files.each do |file|
    # make sure the dir exists for the object file
    dir_name = file.gsub(File.basename(file), '')
    FileUtils.mkdir_p "build/#{dir_name}"
    
    cmd = "#{$cc} #{$arch_settings} #{flags.join(' ')} -c #{file} -o build/#{file}.o"
    puts cmd
    system cmd
  end
  
  # create libchipmunk.a out of the compiled files
  files = Dir.glob("build/src/chipmunk/**/*.o")
  cmd = "#{$ar} cr build/libchipmunk.a #{files.join(' ')}"
  puts cmd
  system cmd
  
  # do ranlib on the library
  cmd = "#{$ranlib} build/libchipmunk.a"
  puts cmd
  system cmd
end


desc "Build the main project and chipmunk if needed TARGET=pre, pixi or host(mac); host is assumed if TARGET is not set"
task :build => :arch_settings do
  # build the chipmunk lib if we can't find build/libchipmunk.a
  if !FileTest.exists? "build/libchipmunk.a"
    Rake::Task[:build_chipmunk].invoke
  end
  
  flags = [
    "-Wno-write-strings",
    "-I#{$pdk_path}/include",
    "-I#{$pdk_path}/include/SDL",
    "-Lbuild",
    "-lchipmunk",
    "-lSDL",
    "-lSDL_image",
    "-lpdl"
  ]
  
  if ENV["TARGET"] == "pre" || ENV["TARGET"] == "pixi"
    flags << "-L#{$pdk_path}/device/lib -Wl,--allow-shlib-undefined"
    flags << "--sysroot=#{$pdk_path}/arm-gcc/sysroot"
    flags << "-DDEVICE"
  else
    flags << "-L#{$pdk_path}/host/lib"
    flags << "-lSDL_image"
    flags << "-framework cocoa"
    flags << "-lSDLmain"
  end
  
  cmd = "#{$gpp} src/main.cpp #{$arch_settings} #{flags.join(' ')} -o main"
  puts cmd
  system(cmd)
end


desc "Clean build files by removing the build directory"
task :clean do
  puts "removing build files..."
  FileUtils.rmtree "build"
  FileUtils.rm "main"
end


desc "Copy the app to /media/internal on the device without creating a package and run the jerk"
task :run do
  copy_bin = "scp -r -P 10022 main root@localhost:/media/internal/pdk_chipmunk"
  puts copy_bin
  system(copy_bin)
  
  copy_asset = "scp -r -P 10022 assets/ball.gif root@localhost:/media/internal/pdk_chipmunk/assets"
  puts copy_asset
  system(copy_asset)
  
  run_cmd = "novacom run file:///media/internal/pdk_chipmunk/main"
  system(run_cmd)
end


desc "Create and install a package to the device"
task :pkg do
  pdk_bin = "/opt/PalmPDK/bin"
  
  # copy the executable and asset file to the package dir
  system("cp main chipmunk_test")
  system("cp assets/ball.gif chipmunk_test/assets")

  puts "packaging..."
  system("#{pdk_bin}/pdk-package chipmunk_test")
  
  puts "installing..."
  system("#{pdk_bin}/pdk-install com.trackera.chipmunk-test_1.0.0_all.ipk")
end
