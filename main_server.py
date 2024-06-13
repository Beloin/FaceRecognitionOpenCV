import ctypes
import os
from flask import Flask, flash, request, redirect, url_for
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = '/tmp'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg'}

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.secret_key = 'super secret key'
app.config['SESSION_TYPE'] = 'filesystem'

lib = ctypes.CDLL('./libdart_interface.so')
my_function = lib.are_equal
my_function.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
my_function.restype = ctypes.c_int


def allowed_file(filename):
    return '.' in filename and \
        filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'image01' not in request.files or 'image02' not in request.files:
            flash('No file part')
            return 'Invalid file', 400

        file = request.files['image01']
        file2 = request.files['image02']

        # If the user does not select a file, the browser submits an
        # empty file without a filename.
        if file.filename == '' or file2.filename == '':
            flash('No selected file')
            return 'Invalid filename', 400

        if file and allowed_file(file.filename) and \
                file2 and allowed_file(file2.filename):
            filename = secure_filename(file.filename)
            full_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(full_path)

            filename2 = secure_filename(file2.filename)
            full_path2 = os.path.join(app.config['UPLOAD_FOLDER'], filename2)
            file2.save(full_path2)

            b_string1 = full_path.encode('utf-8')
            b_string2 = full_path2.encode('utf-8')
            result = my_function(b_string1, b_string2)

            return 'TRUE' if result else 'FALSE', 200
        else:
            return 'File needs to be png|jpeg|jpg', 400

    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=image01>
      <input type=file name=image02>
      <input type=submit value=Upload>
    </form>
    '''


if __name__ == '__main__':
    b_string1 = "./data/named/eminem_1.png".encode('utf-8')
    b_string2 = "./data/named/eminem_2.png".encode('utf-8')
    result = my_function(b_string1, b_string2)
    print(result)
