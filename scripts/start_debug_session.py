import subprocess
import os
import signal

# Configuration
openocd_executable = "openocd"
openocd_config = "board/st_nucleo_f4.cfg"
gdb_executable = "gdb-multiarch"
gdb_target_binary = "../build/app.elf"  # Specify your compiled binary here

# Start OpenOCD
openocd_command = [openocd_executable, "-f", openocd_config]
openocd_process = subprocess.Popen(openocd_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

print("OpenOCD started with PID:", openocd_process.pid)

try:
    # Wait a moment for OpenOCD to initialize
    print("Waiting for OpenOCD to initialize...")
    subprocess.run(["sleep", "2"])

    # Now, start GDB and connect to OpenOCD
    gdb_commands = [
        "target remote :3333",  # Default port where OpenOCD listens
        "monitor reset init",
        "file " + gdb_target_binary,
        "load",
        "monitor reset halt"
    ]
    gdb_command_string = " -ex \"" + "\" -ex \"".join(gdb_commands) + "\""
    gdb_full_command = gdb_executable + gdb_command_string
    
    print("Starting gdb-multiarch with command:", gdb_full_command)
    os.system(gdb_full_command)
    
except KeyboardInterrupt:
    print("Interrupt received! Shutting down.")
finally:
    # Ensure OpenOCD is terminated
    openocd_process.send_signal(signal.SIGINT)
    openocd_process.wait()
    print("OpenOCD terminated.")
