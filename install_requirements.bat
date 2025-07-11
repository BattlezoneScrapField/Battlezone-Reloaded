py -m venv .venv
call .venv\Scripts\activate.bat
py -m pip install -r requirements.txt
call .venv\Scripts\deactivate.bat
pause