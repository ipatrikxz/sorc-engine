import os
import urllib.request
import zipfile

# config
premake_version = "5.0.0-beta1"
premake_zip = f"premake-{premake_version}-windows.zip"
premake_url = f"https://github.com/premake/premake-core/releases/download/v{premake_version}/{premake_zip}"
license_url = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
vendor_dir = os.path.join("..", "vendor/premake/bin")
premake_exe = os.path.join(vendor_dir, "premake5.exe")
license_file = os.path.join(vendor_dir, "LICENSE.txt")

# ensure vendor directory exists
def setup_vendor_dir():
    os.makedirs(vendor_dir, exist_ok=True)

# download premake
def download_premake():
    print(f"📥 downloading {premake_zip}...")
    urllib.request.urlretrieve(premake_url, premake_zip)
    print(f"📜 downloading LICENSE.txt...")
    urllib.request.urlretrieve(license_url, license_file)

# extract premake
def extract_premake():
    print(f"📦 extracting {premake_zip}...")
    with zipfile.ZipFile(premake_zip, 'r') as zip_ref:
        zip_ref.extractall(vendor_dir)
    os.rename(os.path.join(vendor_dir, "premake5.exe"), premake_exe)
    os.remove(premake_zip)

# main
def main():
    setup_vendor_dir()
    if not os.path.exists(premake_exe):
        download_premake()
        extract_premake()
        print(f"✅ premake5 ready in {vendor_dir}")
    else:
        print(f"✅ premake5 already exists in {vendor_dir}")

if __name__ == "__main__":
    main()
