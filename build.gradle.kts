// Top-level build file where you can add configuration options common to all sub-projects/modules.
plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.maven.publish)
}

android {
    namespace = "bitreadercpp"
    compileSdk = 34
    defaultConfig {
        minSdk = 24
        externalNativeBuild {
            cmake {
                arguments.add("-DANDROID_STL=none")
            }
        }
    }
    buildFeatures {
        prefab = true
        prefabPublishing = true
    }

    prefab {
        create("bitreadercpp") {
            headers = "bitreader/include"
        }
    }
    externalNativeBuild {
        cmake {
            path("CMakeLists.txt")
        }
    }
    publishing {
        singleVariant("release")
    }
}
//gradlew h264bitstream:publish
afterEvaluate {
    publishing {
        publications {
            register("bitreadercpp", MavenPublication::class) {
                from(components["release"])
                groupId = "com.homesoft.android"
                artifactId = "bitreadercpp"
                version = "0.2.0"
            }
        }
    }
}
