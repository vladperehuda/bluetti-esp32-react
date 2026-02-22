from pathlib import Path
from shutil import copytree, rmtree, copyfileobj
from subprocess import check_output, Popen, PIPE, STDOUT, CalledProcessError
import os
import gzip

Import("env")

def gzipFile(file):
    with open(file, 'rb') as f_in:
        with gzip.open(file + '.gz', 'wb') as f_out:
            copyfileobj(f_in, f_out)
    os.remove(file)

def buildWeb():
    os.chdir("frontend")
    print("Building frontend with npm")
    try:
        env.Execute("npm install")
        env.Execute("npm run build")
        buildPath = Path("dist")
        wwwPath = Path("../data/www")
        if wwwPath.exists() and wwwPath.is_dir():
            rmtree(wwwPath)        
        print("Copying frontend to data directory")
        copytree(buildPath, wwwPath)
        for currentpath, folders, files in os.walk(wwwPath):
            for file in files:
                gzipFile(os.path.join(currentpath, file))
    finally:
        os.chdir("..")

if (len(BUILD_TARGETS) == 0 or "upload" in BUILD_TARGETS):
    buildWeb()
else:
    print("Skipping build frontend step for target(s): " + ", ".join(BUILD_TARGETS))
