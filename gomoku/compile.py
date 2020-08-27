import subprocess
import os

os.chdir("srcs")
subprocess.call(["cl", "/EHsc", "*.cpp", "/link", "/out:../pbrain-RENNES-Tual.Nathan.exe"])
