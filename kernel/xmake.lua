target("kernel")
    set_toolchains("clangpe")
    set_filename("kernel.exe")
    set_targetdir(".")
    add_files("src/*.c", "src/**/*.c");
    add_files("src/*.S", "src/**/*.S");
    add_cflags("-target aarch64-none-windows -ffreestanding")
    add_asflags("-target aarch64-none-windows -ffreestanding -nostdlib -fno-rtti")
    add_ldflags("/machine:arm64 /subsystem:native /entry:kLoaderEntry /base:0x40000000", {force = true})



toolchain("clangpe")
    set_toolset("cc", "clang");
    set_toolset("as", "clang");
    set_toolset("ld", "lld-link")
toolchain_end();