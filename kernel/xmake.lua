target("kernel")
    set_toolchains("clangpe")
    set_filename("kernel.exe")
    set_targetdir(".")
    add_files("src/*.c", "src/**/*.c");
    add_files("src/*.asm", "src/**/*.asm");
    add_cflags("-target x86_64-none-windows -ffreestanding")
    add_ldflags("/machine:amd64 /subsystem:native /entry:kLoaderEntry /base:0x20000", {force = true})



toolchain("clangpe")
    set_kind("standalone")
    set_toolset("cc", "clang")
    set_toolset("as", "nasm")
    add_asflags("-f win64", {force = true})
    set_toolset("ld", "lld-link")
toolchain_end();