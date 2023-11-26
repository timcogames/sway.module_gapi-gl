@Library("sway_jenkins_pipeline_docker") _

import org.jenkinsci.plugins.pipeline.modeldefinition.Utils

import java.util.Optional
import sway.jenkins_pipeline.docker.shell.Executor
import sway.jenkins_pipeline.docker.shell.ScriptExecutor
import sway.jenkins_pipeline.docker.model.OSType
import sway.jenkins_pipeline.docker.model.ArchitectureType
import sway.jenkins_pipeline.docker.model.TargetPlatform
import sway.jenkins_pipeline.docker.entity.Entity
import sway.jenkins_pipeline.docker.entity.ImageEntity
import sway.jenkins_pipeline.docker.entity.MultiarchImageEntity
import sway.jenkins_pipeline.docker.entity.ContainerEntity
import sway.jenkins_pipeline.docker.command.BuildImageCommand
import sway.jenkins_pipeline.docker.command.BuildImageCommandHandler
import sway.jenkins_pipeline.docker.command.CommandResult
import sway.jenkins_pipeline.docker.query.ImageInspectQuery
import sway.jenkins_pipeline.docker.query.ImageInspectQueryHandler

String DOCKER_PATH = "/Applications/Docker.app/Contents/Resources/bin"
String CMAKE_PATH = "/opt/homebrew/Cellar/cmake/3.22.1/bin"

String MODULE_GAPI_GL_CONTAINER_ID = ""
String MODULE_GAPI_GL_CONTAINER_NAME = "cntr"

String MODULE_GAPI_GL_IMAGE_ID = ""
String MODULE_GAPI_GL_IMAGE_REGISTRY_NAMESPACE = "bonus85"
String MODULE_GAPI_GL_IMAGE_LOCAL_NAMESPACE = "local"
String MODULE_GAPI_GL_IMAGE_NAME = "sway.module_gapi-gl"
String MODULE_GAPI_GL_IMAGE_TAG = "latest"
String MODULE_GAPI_GL_IMAGE_REFERENCE_NAME = "${MODULE_GAPI_GL_IMAGE_NAME}:${MODULE_GAPI_GL_IMAGE_TAG}"

String SELECTED_BRANCH_NAME = ""
String SELECTED_BUILD_TYPE = ""
String SELECTED_PLATFORN_LIST_STR = ""
String APPLIED_THIRD_PARTY_DIR = ""

boolean ENABLED_TESTS = false
boolean ENABLED_COVERAGE = false

List<String> SELECTED_PLATFORN_LIST = []

def jenkinsUtils

ContainerEntity dockerContainerEntity = new ContainerEntity(MODULE_GAPI_GL_CONTAINER_NAME)
MultiarchImageEntity dockerMultiarchImageEntity = new MultiarchImageEntity(
  MODULE_GAPI_GL_IMAGE_REGISTRY_NAMESPACE, MODULE_GAPI_GL_IMAGE_NAME, MODULE_GAPI_GL_IMAGE_TAG)
List<ImageEntity> dockerImageEntities = new ArrayList<ImageEntity>()

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
      // def targetPlatform = SELECTED_PLATFORN_LIST_STR.tokenize("/")[0];
      // def targetArch = SELECTED_PLATFORN_LIST_STR.substring(targetPlatform.size() + 1)

      List<TargetPlatform> platforms = [ 
        new TargetPlatform(OSType.LINUX, ArchitectureType.AARCH64)
        // new TargetPlatform(OSType.LINUX, ArchitectureType.X64) 
      ]

      platforms.eachWithIndex { item, index ->
        dockerImageEntities.add(new ImageEntity(MODULE_CORE_IMAGE_LOCAL_NAMESPACE, MODULE_CORE_IMAGE_NAME, MODULE_CORE_IMAGE_TAG, item))

        Map<String, String> envs = [:]
        Map<String, String> args = [
          "ENABLED_COVERAGE": base.booleanToCMakeStr(ENABLED_COVERAGE),
          "ENABLED_TESTS": base.booleanToCMakeStr(ENABLED_TESTS)
        ]

        BuildImageCommand buildImageCmd = new BuildImageCommand(dockerImageEntities.get(index), 
          "${env.WORKSPACE}", "gcc-linux-xarch.Dockerfile", envs, args, "module_gapi_gl-${SELECTED_BUILD_TYPE}")
        BuildImageCommandHandler buildImageCmdHandler = new BuildImageCommandHandler(new ScriptExecutor(DOCKER_PATH))
        CommandResult<String> buildImageCmdHandlerResult = buildImageCmdHandler.handle(buildImageCmd)

        if (buildImageCmdHandlerResult.succeeded) {
          ImageInspectQuery imageInspectQry = new ImageInspectQuery(dockerImageEntities.get(index))
          ImageInspectQueryHandler imageInspectQryHandler = new ImageInspectQueryHandler(new ScriptExecutor(DOCKER_PATH))
          Map<String, String> imageInspectQryHandlerResult = imageInspectQryHandler.handle(imageInspectQry)
          dockerImageEntities.get(index).setId(imageInspectQryHandlerResult.id)
        }
      }
    }

    stage("Push") {
      // docker push sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG-amd64

      // docker manifest create \
      //           sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG \
      //   --amend sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG-amd64 \
      //   --amend sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG-arm32v7 \
      //   --amend sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG-arm64v8

      // docker manifest push sway/MODULE_GAPI_GL_IMAGE_NAME:MODULE_GAPI_GL_IMAGE_TAG
    }
  } finally {
    stage("cleanup") {
      // Empty
    }
  }
}
