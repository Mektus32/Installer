#!venv/bin/python
import fnmatch
import json
import os

import flask
from flask import Flask, jsonify, request, Response

app = Flask(__name__)

with open('config.json', 'r') as file:
    config = json.loads(file.read())

programs = [
]


def fill_programs():
    programs_path = config.get('programs_dir', os.curdir.join('programs'))
    for program_dir in os.listdir(programs_path):
        program_path = os.path.join(programs_path, program_dir)
        versions = {}
        for version_dir in os.listdir(program_path):
            for version, _, files in os.walk(os.path.join(program_path, version_dir)):
                zip_files = fnmatch.filter(files, '*.zip')
                if len(zip_files) == 1:
                    versions[version[version.rfind('/') + 1:]] = os.path.join(version, zip_files[0])
                elif len(zip_files) > 1:
                    print(f"ERROR: More one zip file in directory {version}")
                else:
                    print(f"ERROR: No one zip file in directory {version}")
        if len(versions):
            program = {'name': program_dir, 'versions': versions}
            global programs
            programs.append(program)


@app.route('/v1/applications-info', methods=['GET'])
def get_applications_info():
    return jsonify(
        [{'name': program['name'], 'versions': [version for version in program['versions'].keys()]} for program in
         programs])


@app.route('/v1/application', methods=['GET'])
def get_application():
    program_name = request.args.get('name')
    version = request.args.get('version')
    if program_name is None:
        return Response("{'message': 'Expected program name in query'}", status=400, mimetype='application/json')
    elif version is None:
        return Response("{'message': 'Expected version in query'}", status=400, mimetype='application/json')
    file_path = None
    for program in programs:
        if program['name'] == program_name:
            file_path = program['versions'].get(version)
    if file_path:
        return flask.send_file(file_path)
    else:
        print(f"WARNING: No program {program_name} with version {version}")
        return Response("{'message': 'No such version or program'}", status=400, mimetype='application/json')


if __name__ == '__main__':
    fill_programs()
    app.run(host=config.get('ip', '127.0.0.1'), debug=True)
