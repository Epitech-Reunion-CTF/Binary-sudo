<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Calculator</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }
        .container {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 80%;
            max-width: 600px;
        }
        h1 {
            font-size: 24px;
            margin-bottom: 20px;
        }
        form {
            margin-bottom: 20px;
        }
        input[type="text"] {
            width: calc(100% - 22px);
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        input[type="submit"] {
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            background-color: #007BFF;
            color: #fff;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #0056b3;
        }
        pre {
            background-color: #f4f4f4;
            padding: 10px;
            border-radius: 4px;
            border: 1px solid #ccc;
            white-space: pre-wrap;
            word-wrap: break-word;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Calculator</h1>
        <form method="GET">
            <input type="text" name="expression" placeholder="Enter expression (e.g., 2+2)" required>
            <input type="submit" value="Calculate">
        </form>
        <?php
        if (isset($_GET['expression'])) {
            $expression = $_GET['expression'];
            echo '<pre>Result: ' . htmlspecialchars(shell_exec("echo '$expression'")) . '</pre>';
            $command = "echo '$expression' | bc";
            $result = shell_exec($command);
                echo '<pre>Result: ' . htmlspecialchars($result) . '</pre>';
        }
        ?>
    </div>
</body>
</html>