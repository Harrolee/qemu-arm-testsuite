# This will publish tests to the broker.
from fastapi import FastAPI, File, UploadFile
from fastapi.responses import FileResponse 
from os.path import exists
#import test_publisher as test_pub
import aiofiles

app = FastAPI()

code_dir = "/fastapi/code_to_emulate/"
filename = None


@app.post("/upload-code/", status_code=201)
async def create_upload_file(file: UploadFile = File(...)):
    # when the user uploads a file, the filename will be stored in memory.
    # this is the file that 
    global filename
    filename = file.filename
    code = file.read()
    # write code to code_dir

    async with aiofiles.open(f'{code_dir}/{filename}', 'wb') as upload:
        while content := await file.read(1024):
            await upload.write(content)
            
    return {"filename": file.filename}

@app.get("/get-code/{filename}")
async def serve_code(filename):
    filepath = f'{code_dir}{filename}'
    if exists(filepath):
        return FileResponse(filepath)
    return f"File does not exist at {filepath}"

@app.get("/are-we-ready/")
def check_for_file():
    filepath = f'{code_dir}{filename}'
    if exists(filepath):
        return filename
    return "no-file"
    # returns true if the path exists, false if not.








"""
testing functions:

@app.get("/get-bin")
async def serve_code():
    return FileResponse('/fastapi/code_to_emulate/test')

@app.get("/get-apple")
async def serve_code():
    return FileResponse(f'{code_dir}apple.txt')

@app.get("/test")
async def serve_code():
    return "this works"
"""

# run tests on emulated devices
@app.post("/runall")
def run_all_tests():
    return test_pub.publish('run all')