<?php

call_user_func(function()
{
    require_once dirname(__DIR__) . '/scripts/bootstrap.php';
    try {
        if (!isset($_ENV['REQUEST_URI'])) {
            throw new Exception('env.REQUEST_URI was not set');
        }

        $uri = $_ENV['REQUEST_URI'];

        $di = new Project\Di();
        $di->set('mysql', new Project\Database('mariadb', 'myuser', 'secret', 'mydb'));

        $rawPayload = file_get_contents('php://input');
        $payload = json_decode($rawPayload, true);

        if (!empty($rawPayload) && json_last_error()) {
            throw new Project\BadRequestException();
        }

        $controller = new Project\Controller();
        $controller->register('#^/$#', ['GET'], new Project\Page\Root($di));
        $controller->register('#^/init/?$#', ['POST'], new Project\Page\Init($di));
        $controller->register('#^/type/?$#', ['GET'], new Project\Page\Types($di));
        $controller->register('#^/column/?#', ['GET'], new Project\Page\Column($di));
        $controller->register('#^/company/?#', ['GET'], new Project\Page\Company($di));
        $controller->register('#^/language/?$#usi', ['GET'], new Project\Page\Languages($di));
        $controller->register('#^/language/exclude_by_type/(?P<exclude_type>[^/]+)/?$#u', ['GET'], new Project\Page\LanguagesExcludingType($di));
        $controller->register('#^/language/familiar/(?P<company_name>[^/]+)/?$#u', ['GET'], new Project\Page\Familiar($di));
        $controller->register('#^/language/column/(?P<column_name>[^/]+)/?$#u', ['GET'], new Project\Page\LanguagesColumn($di));

        ob_start();
        /** @var $invoker \Project\Page\PageAbstract */
        list($invoker, $arguments) = $controller->getInvokerAndArguments($_ENV['REQUEST_URI'], $_ENV['REQUEST_METHOD']);
        $result = $invoker->invoke($payload, $arguments);
        $headers = $invoker->getHeaders();
        foreach ($headers as $header) {
            header($header);
        }

        if (is_object($result) || is_array($result)) {
            header("Content-Type: application/json");
            echo json_encode($result, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
            return;
        }

        $contents = ob_get_clean();
        echo $contents;
    } catch (\Project\UnknownInvokerException $exception) {
        header("HTTP/1.0 404 Not Found");
        print_r($exception);
    } catch (\Project\ClientException $exception) {
        header("HTTP/1.0 400 Bad Request");
        print_r($exception);
    } catch (Exception $exception) {
        header("HTTP/1.0 500 Internal Server Error");
        print_r($exception);
    }
});

