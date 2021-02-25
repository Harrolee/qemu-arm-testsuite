# This will publish tests to the broker.
from fastapi import FastAPI, File, UploadFile
import test_publisher as test_pub

app = FastAPI()


@app.post("/upload-code/")
async def create_upload_file(file: UploadFile = File(...)):
    return {"filename": file.filename}

# run tests on emulated devices
@app.post("/runall")
def run_all_tests():
    return test_pub.publish('run all')