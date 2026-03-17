import psycopg2

def get_connection():
 return psycopg2.connect(
 dbname="note_manager",
 user="postgres",
 password="200718za",
 host="localhost",
 port="5432"
 )