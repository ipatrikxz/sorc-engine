import os
import urllib.request
import zipfile
import subprocess
import platform

# config
premake_version = "5.0.0-beta7"
premake_zip = f"premake-{premake_version}-windows.zip"
premake_url = f"https://github.com/premake/premake-core/releases/download/v{premake_version}/{premake_zip}"
license_url = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
vendor_dir = os.path.join("..", "vendor/premake/bin")
premake_exe = os.path.join(vendor_dir, "premake5.exe")
license_file = os.path.join(vendor_dir, "LICENSE.txt")
generate_script = os.path.abspath("./Win_Generate_Project.bat")

def setup_vendor_dir():
    os.makedirs(vendor_dir, exist_ok=True)

def download_premake():
    print(f"📥 downloading {premake_zip}...")
    urllib.request.urlretrieve(premake_url, premake_zip)
    urllib.request.urlretrieve(license_url, license_file)

def extract_premake():
    print(f"📦 extracting {premake_zip}...")
    with zipfile.ZipFile(premake_zip, 'r') as zip_ref:
        zip_ref.extractall(vendor_dir)
    os.rename(os.path.join(vendor_dir, "premake5.exe"), premake_exe)
    os.remove(premake_zip)

def generate_project():
    if platform.system() == "Windows":
        if os.path.exists(generate_script):
            print("🔨 running project generation script...")
            try:
                subprocess.call([generate_script, "nopause"])
                print("✅ project generated!")
            except subprocess.CalledProcessError as e:
                print(f"❌ project generation failed: {e}")
        else:
            print(f"⚠️ skipping generation: premake5 or {generate_script} missing")

def main():
    setup_vendor_dir()
    premake_success = False
    if not (os.path.exists(premake_exe)):
        try:
            download_premake()
            extract_premake()
            premake_success = True
            print(f"✅ premake5 ready in {vendor_dir}")
        except Exception as e:
            print(f"❌ setup failed: {e}")
    else:
        print(f"✅ premake5 already exist")
        premake_success = True

    if premake_success:
        generate_project()

if __name__ == "__main__":
    main()