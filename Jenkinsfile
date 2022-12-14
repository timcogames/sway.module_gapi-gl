pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                git url: 'https://github.com/timcogames/sway.module_gapi-gl.git', branch: 'master'
                sh "mkdir build && cd ./build"
            }
        }
    }
}
