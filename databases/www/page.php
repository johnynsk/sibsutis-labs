<?php

call_user_func(function()
{
    require_once dirname(__DIR__) . '/scripts/bootstrap.php';
    $handler = function (Exception $exception) {
        echo json_encode([
            'error' => [
                'message' => $exception->getMessage(),
                'trace' => $exception->getTrace(),
                'class' => get_class($exception),
            ]
        ], JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
    };

    try {
        if (!isset($_ENV['REQUEST_URI'])) {
            throw new Exception('env.REQUEST_URI was not set');
        }

        $db = new Project\Database('mariadb', 'myuser', 'secret', 'mydb');

        $rawPayload = file_get_contents('php://input');
        $payload = json_decode($rawPayload, true);

        if (!empty($rawPayload) && json_last_error()) {
            throw new Project\Exception\Client("Payload should be in the json format.");
        }

        $controller = new Project\Controller();
        $controller->register('#^/$#', ['GET'], new Project\Page\Root($db));
        $controller->register('#^/init/?$#', ['POST'], new Project\Page\Init($db));
        $controller->register('#^/type/?$#', ['GET'], new Project\Page\Types($db));
        $controller->register('#^/column/?#', ['GET'], new Project\Page\Column($db));
        $controller->register('#^/company/?#', ['GET'], new Project\Page\Company($db));
        $controller->register('#^/language/?$#usi', ['GET'], new Project\Page\Languages($db));
        $controller->register('#^/language/exclude_by_type/(?P<exclude_type>[^/]+)/?$#u', ['GET'], new Project\Page\LanguagesExcludingType($db));
        $controller->register('#^/language/familiar/(?P<company_name>[^/]+)/?$#u', ['GET'], new Project\Page\LanguagesFamiliar($db));
        $controller->register('#^/language/column/(?P<column_name>[^/]+)/?$#u', ['GET'], new Project\Page\LanguagesColumn($db));

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
    } catch (\Project\Exception\UnknownUrl $exception) {
        header("HTTP/1.0 404 Not Found");
        $handler($exception);
    } catch (\Project\Exception\Client $exception) {
        header("HTTP/1.0 400 Bad Request");
        $handler($exception);
    } catch (Exception $exception) {
        header("HTTP/1.0 500 Internal Server Error");
        $handler($exception);
    }
});

