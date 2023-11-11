@Library("sway_jenkins_pipeline_docker") _

import org.jenkinsci.plugins.pipeline.modeldefinition.Utils

import java.util.Optional
import sway.jenkins_pipeline.docker.model.OSType
import sway.jenkins_pipeline.docker.model.ArchitectureType
import sway.jenkins_pipeline.docker.model.TargetPlatform
import sway.jenkins_pipeline.docker.entity.ImageEntity
import sway.jenkins_pipeline.docker.command.BuildImageCommand
import sway.jenkins_pipeline.docker.command.BuildImageCommandLine
import sway.jenkins_pipeline.docker.command.BuildImageCommandHandler
import sway.jenkins_pipeline.docker.command.CommandResult

def DOCKER_PATH = "/Applications/Docker.app/Contents/Resources/bin"
def CMAKE_PATH = "/opt/homebrew/Cellar/cmake/3.22.1/bin"

def MODULE_GAPI_GL_CONTAINER_NAME = "sway"
def MODULE_GAPI_GL_CONTAINER_ID = ""
def MODULE_GAPI_GL_IMAGE_TAG = "latest"
def MODULE_GAPI_GL_IMAGE_NAME = "${MODULE_GAPI_GL_CONTAINER_NAME}/module_gapi-gl"
def MODULE_GAPI_GL_IMAGE_FULLNAME = "${MODULE_GAPI_GL_IMAGE_NAME}:${MODULE_GAPI_GL_IMAGE_TAG}"
def MODULE_GAPI_GL_IMAGE_ID = ""

def SELECTED_BRANCH_NAME = ""
def SELECTED_BUILD_TYPE = ""
def SELECTED_PLATFORN_LIST = []
def SELECTED_PLATFORN_LIST_STR = ""
def APPLIED_THIRD_PARTY_DIR = ""
def ENABLED_TESTS = ""
def ENABLED_COVERAGE = ""

def jenkinsUtils

node {
  try {
    stage("Clone repository") {
      SELECTED_BRANCH_NAME = input(message: "Select active branch", parameters: [
        [$class: "ChoiceParameterDefinition", 
          choices: "develop\nmaster", 
          name: "Active branch", 
          description: "Select option the relevant branch"]
      ])

      git url: "https://github.com/timcogames/sway.module_gapi-gl.git", branch: "${SELECTED_BRANCH_NAME}"
      sh "git submodule update --init --recursive"

      dir("submodules/sway.module_core/scripts") {
        jenkinsUtils = load "sway.jenkins_pipeline-docker/vars/Utils.groovy"
        jenkinsUtils.approveSignatures([
          "method groovy.lang.GroovyObject getProperty java.lang.String",
          "staticMethod org.codehaus.groovy.runtime.DefaultGroovyMethods indexed java.lang.Iterable"
        ])
      }
    }

    stage("Build options") {
      def optionParams = [ choice(name: "BUILD_TYPE", choices: "debug\nrelease", description: "Select the build type") ]

      ArchitectureType.values().collect() { it.alias }
        .indexed().collect { index, item ->
          optionParams.add(booleanParam(name: item, defaultValue: index == 0 ? true : false))
      }

      optionParams.add(string(name: "THIRD_PARTY_DIR", defaultValue: "/opt/third_party", description: ""))
      optionParams.add(booleanParam(name: "TESTS", defaultValue: true, description: ""))
      optionParams.add(booleanParam(name: "COVERAGE", defaultValue: false, description: ""))

      def options = input(message: "Build options", ok: "Run", parameters: optionParams)

      ArchitectureType.values().each { item -> 
        if (options."${item.alias}") {
          SELECTED_PLATFORN_LIST.add("linux/${item.alias}");
        }
      }

      SELECTED_BUILD_TYPE = options["BUILD_TYPE"]
      SELECTED_PLATFORN_LIST_STR = SELECTED_PLATFORN_LIST.join(",")
      APPLIED_THIRD_PARTY_DIR = options["THIRD_PARTY_DIR"]
      ENABLED_TESTS = options["TESTS"]
      ENABLED_COVERAGE = options["COVERAGE"]
    }

    stage("Build:docker gcc-linux-xarch") {
      def targetPlatform = SELECTED_PLATFORN_LIST_STR.tokenize("/")[0];
      def targetArch = SELECTED_PLATFORN_LIST_STR.substring(targetPlatform.size() + 1)

      def imageTag = "${MODULE_GAPI_GL_IMAGE_TAG}-${targetArch.replace("/", "_")}"
      def platform = new TargetPlatform(OSType.LINUX, ArchitectureType.AARCH64)

      def workspace = "$WORKSPACE/gcc-linux-xarch.Dockerfile"
      
      def image = new ImageEntity(MODULE_GAPI_GL_IMAGE_NAME, imageTag, platform)

      def imageCommand = new BuildImageCommand(image.nameWithTag(), image.platform, "$workspace", [
        "ENABLED_TESTS": jenkinsUtils.booleanToCMakeStr(ENABLED_TESTS), "ENABLED_COVERAGE": jenkinsUtils.booleanToCMakeStr(ENABLED_COVERAGE) ],
        "$WORKSPACE")
      imageCommand.line.addTarget("module_gapi_gl-${SELECTED_BUILD_TYPE}")

      def imageCommandHandler = new BuildImageCommandHandler(DOCKER_PATH)
      def result = imageCommandHandler.execute(imageCommand)
      echo "$result.message"
    }
  } finally {
    stage("cleanup") {
      // Empty
    }
  }
}
