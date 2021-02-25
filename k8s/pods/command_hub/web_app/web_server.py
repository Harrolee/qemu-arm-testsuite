# This will publish tests to the broker.
from fastapi import FastAPI, File, UploadFile
from fastapi.responses import FileResponse 
import test_publisher as test_pub


app = FastAPI()

code_dir = "/fastapi/code_to_emulate/"
filename = None

@app.post("/upload-code/")
async def create_upload_file(file: UploadFile = File(...)):
    # write file to file
    filename = file.filename
    code = file.read()
    return {"filename": file.filename, "filesize": code.__sizeof__()}

@app.get("/get-code")
async def serve_code():
    return FileResponse(f'{code_dir}/{filename}')

@app.get("/get-apple")
async def serve_code():
    return FileResponse(f'{code_dir}apple.txt')

@app.get("/test")
async def serve_code():
    return "this works"


# run tests on emulated devices
@app.post("/runall")
def run_all_tests():
    return test_pub.publish('run all')