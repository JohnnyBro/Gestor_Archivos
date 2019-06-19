import qbs

CppApplication {
    consoleApplication: true
    files: [
        "analizador.c",
        "analizador.h",
        "estructuras.h",
        "fdisk.c",
        "fdisk.h",
        "main.c",
        "mkdisk.c",
        "mkdisk.h",
        "mrdisk.c",
        "mrdisk.h",
        "reportes.c",
        "reportes.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
