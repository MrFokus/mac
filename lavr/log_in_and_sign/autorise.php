<?php
    session_start();
    $login=$_POST['login'];
    $pass=$_POST['pass'];
    $hash = md5($pass);
    $check_login="SELECT * FROM USER WHERE login = '$login' AND password='$hash'";
    $mysql=new mysqli('localhost','root','root','MY_DATA');
    $check=$mysql->query($check_login);
    $user=$check->fetch_assoc();
    echo $hash;
    // var_dump($login,$pass,$name,$date_b,$tel);
    if(count($user)==0){
        $_SESSION['Message_no_user'] = "Неправильный логин или пароль";
        header('Location: log.php');
        exit();
    }
    else{
        
        setcookie('user_id',$user['user_id'],time()+3600*24*30,"/");
        header('Location: ../account/account.php');
    }
?>