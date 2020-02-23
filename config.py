import os  # system()


def can_build(platform):
    if platform == "x11":
        has_pulse = os.system("pkg-config --exists libpulse-simple") == 0
        has_alsa = os.system("pkg-config --exists alsa") == 0
        return has_pulse or has_alsa
    elif platform in ["windows", "osx", "iphone", "android"]:
        return True
    else:
        return False


def configure(env):
    pass


def get_doc_classes():
    return [
        "STTConfig",
        "STTQueue",
        "STTRunner",
        "STTError",
    ]


def get_doc_path():
    return "doc"
