# Test d'envoi de requête contenant un simple message texte sur un bot telegram
import requests

url = "https://api.telegram.org/bot5647128476:AAHgpPJ625ZpgXkIayld5_qF4XiXBvTZVtM/sendMessage?chat_id=5288792176&text=bonjour"
r = requests.get(url)
print(r)