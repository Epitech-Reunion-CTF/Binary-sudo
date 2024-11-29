from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/execute', methods=['POST'])
def execute_command():
    try:
        data = request.get_json()
        command = data.get('command')
        restricted_commands = ['rm', 'shutdown', 'reboot']
        if any(cmd in command for cmd in restricted_commands):
            return jsonify({'status': 'error', 'message': 'Command not allowed.'})
        if not command:
            return jsonify({'status': 'error', 'message': 'No command provided.'})

        # Exécuter la commande et récupérer la sortie
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return jsonify({
            'status': 'success',
            'output': result.stdout.strip() or result.stderr.strip()
        })
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
