import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd






# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE personid=:id", id=session["user_id"])
    index = []
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
    for item in stocks:
        i = item["symbol"]
        j = db.execute("SELECT SUM(shares) FROM transactions WHERE personid=:id AND symbol=:i", id=session["user_id"], i=i)[0]["SUM(shares)"]
        k = lookup(i)["price"]
        if j > 0:
            index.append({"stock": i, "name":lookup(i)["name"], "shares": j, "price": k, "value": j*k})
    total = sum(item["value"] for item in index) + cash
    return render_template("index.html", index=index, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method=="GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)["price"]
        money = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
        if not lookup(symbol):
            return apology("Incorrect symbol.")
        symbol = symbol.upper()
        try:
            i = int(shares)
        except:
            return apology("Number of shares must be positive and a whole number.")
        if i < 0:
            return apology("Number of shares must be positive and whole number.")
        value = i * price
        if money < value:
            return apology("Insufficient funds.")
        db.execute("INSERT INTO transactions (personid, shares, symbol, price) VALUES(:id, :share, :symbol, :price)", id=session["user_id"], share=i, symbol=symbol, price=price)
        db.execute("UPDATE users SET cash=:money WHERE id=:id", money=money-value, id=session['user_id'])
        return redirect("/")



@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT symbol, shares, time, price FROM transactions WHERE personid=:id", id=session["user_id"])
    #print(history)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username LOGGED OUT", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password LOGGED OUT", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method=="GET":
        return render_template("quote.html")
    if request.method=="POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if password.islower() or password.isalpha():
            return apology("Password must contain at least one uppercase letter and number/symbol.")
        if len(password) < 8:
            return apology("Password must be at least 8 characters long.")
        if  password != confirmation:
            return apology("Passwords do not match")
        if not username:
            return apology("Must enter username")
        if not password:
            return apology("Must enter password")
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=generate_password_hash(password))
        return redirect("/")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method=="GET":
        return render_template("sell.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)["price"]
        money = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
        if not lookup(symbol):
            return apology("Incorrect symbol.")
        symbol = symbol.upper()
        try:
            i = int(shares)
        except:
            return apology("Number of shares must be positive and a whole number.")
        if i < 0:
            return apology("Number of shares must be positive and whole number.")
        share = db.execute("SELECT SUM(shares) FROM transactions WHERE personid=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol)[0]["SUM(shares)"]
        if share == 0 or not share:
            return apology(f"You don't own any {lookup(symbol)['name']} shares.")
        if i > share:
            return apology("Insufficient shares.")
        db.execute("INSERT INTO transactions (personid, shares, symbol, price) VALUES(:id, :share, :symbol, :price)", id=session["user_id"], share=-i, symbol=symbol, price=price)
        db.execute("UPDATE users SET cash=:money WHERE id=:id", money=money+(price*i), id=session['user_id'])
        return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
